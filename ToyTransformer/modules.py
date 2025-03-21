import torch
from torch import nn

d_model = 512
d_k = 64
d_v = 64

class ScaleDotProductAttention(nn.Module):
    def __init__(self):
        super(ScaleDotProductAttention, self).__init__()

    def forward(self, query, key, value, mask=None):
        '''
        Q = bs * d_q * d_model
        K = bs * d_k * d_model
        V = bs * d_v * d_model
        OUTPUT = bs * d_q * d_model
        '''
        matmul_qk = torch.matmul(query, key.transpose(1, 2)) # d_q * d_model MATMUL d_model * d_k = d_q * d_k
        scale = query.shape[-1] ** 0.5 # d_model
        attention = torch.softmax(matmul_qk / scale, dim=-1) # d_q * d_k
        if mask is not None:
            attention = attention.masked_fill(mask == 0, float('-inf'))
        output = torch.matmul(attention, value) # d_q * d_k MATMUL d_k * d_model = d_q * d_model
        return output
    
class MultiHeadAttention(nn.Module):
    def __init__(self, heads=8):
        '''
        Q = bs * d_q * d_model
        K = bs * d_k * d_model
        V = bs * d_v * d_model
        OUTPUT = bs * d_q * d_model
        '''
        super(MultiHeadAttention, self).__init__()
        self.num_heads = heads
        self.weight_Q = nn.Linear(d_model, d_k)
        self.weight_K = nn.Linear(d_model, d_k)
        self.weight_V = nn.Linear(d_model, d_v)
        self.weight_O = nn.Linear(d_v * self.num_heads, d_model)
        self.attention_module = ScaleDotProductAttention()

    def forward(self, query, key, value, mask=None):
        step_size = query.shape[1] // self.num_heads
        output = torch.cat(
            [
                self.attention_module(
                    self.weight_Q(query[:, :, :]),
                    self.weight_K(key[:, :, :]),
                    self.weight_V(value[:, :, :]), # bs * d_q * d_k
                    mask,
                )
                for i in range(self.num_heads)
            ],1
        ).view(query.shape[0], query.shape[1], d_v * self.num_heads) # bs * d_q * d_model
        output = self.weight_O(output) # bs * d_q * d_model
        return output
    
class FFN(nn.Module):
    def __init__(self):
        super(FFN, self).__init__()
        self.d_ffn = 2048
        self.linear1 = nn.Linear(d_model, self.d_ffn)
        self.linear2 = nn.Linear(self.d_ffn, d_model)
        self.relu = nn.ReLU()
    
    def forward(self, x):
        return self.linear2(self.relu(self.linear1(x))) # bs * d_q * d_model
    
class PositionEncoding(nn.Module):
    def __init__(self):
        super(PositionEncoding, self).__init__()
    
    def forward(self, x):
        # Input: bs * d_q * d_model
        # Output: bs * d_q * d_model
        pos = torch.arange(0, x.shape[1], dtype=torch.float).unsqueeze(0)
        pos = pos.repeat(x.shape[0], 1)
        pos = pos.unsqueeze(-1).expand_as(x)
        return x + pos
    
class Encoder(nn.Module):
    def __init__(self):
        super(Encoder, self).__init__()
        self.mha = MultiHeadAttention()
        self.ffn = FFN()
        self.layer_norm1 = nn.LayerNorm(d_model)
        self.layer_norm2 = nn.LayerNorm(d_model)
    
    def forward(self, x, mask=None):
        attention = self.mha(x, x, x, mask)
        attention = self.layer_norm1(x + attention)
        ffn = self.ffn(attention)
        ffn = self.layer_norm2(attention + ffn)
        return ffn
    
class Decoder(nn.Module):
    def __init__(self):
        super(Decoder, self).__init__()
        self.masked_mha = MultiHeadAttention()
        self.mha = MultiHeadAttention()
        self.ffn = FFN()
        self.layer_norm1 = nn.LayerNorm(d_model)
        self.layer_norm2 = nn.LayerNorm(d_model)
        self.layer_norm3 = nn.LayerNorm(d_model)
    
    def forward(self, x, encoder_output, mask=None):
        mask = torch.triu(torch.ones_like(x), 1)
        mask = mask.masked_fill(mask == 1, float('-inf'))
        attention = self.masked_mha(x, encoder_output, encoder_output, mask)
        attention = self.layer_norm1(x + attention)
        attention_mha = self.mha(attention, encoder_output, encoder_output)
        attention_mha = self.layer_norm2(attention + attention_mha)
        ffn = self.ffn(attention_mha)
        ffn = self.layer_norm3(attention_mha + ffn)
        return ffn
    
class Transformer(nn.Module):
    def __init__(self):
        '''
        Assume N=1.
        '''
        super(Transformer, self).__init__()
        self.pe = PositionEncoding()
        self.encoder = Encoder()
        self.decoder = Decoder()
    
    def forward(self, x, encoder_output, mask=None):
        x = self.pe(x)
        x = self.encoder(x, mask)
        x = self.decoder(x, encoder_output, mask)
        return x