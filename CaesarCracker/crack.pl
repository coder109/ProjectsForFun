
sub readInput {
    print "Enter the caesar cipher: ";
    $input = <STDIN>;
    chomp($input);
    return $input;
}

sub calcChar {
    $inputChar = $_[0];
    $offsetValue = $_[1];
    if (ord($inputChar) >= ord("A") && ord($inputChar) <= ord("Z")) {
        return chr((ord($inputChar) - ord("A") + $offsetValue) % 26 + ord("A"));
    } elsif (ord($inputChar) >= ord("a") && ord($inputChar) <= ord("z")) {
        return chr((ord($inputChar) - ord("a") + $offsetValue) % 26 + ord("a"));
    } else {
        return $inputChar;  # Return non-alphabetic characters unchanged
    }
}

sub getAllResultCaesar {
    $inputStr = $_[0];
    @result = ();
    for ($i = 0; $i < 26; $i++) {
        $curr_result = "";
        for ($j = 0; $j < length($inputStr); $j++) {
            $c = substr($inputStr, $j, 1);
            $curr_result .= calcChar($c, $i);  # Always call calcChar
        }
        push(@result, $curr_result);
    }
    return @result;
}

$input = readInput();
@result = getAllResultCaesar($input);
print "Possible results:\n";
for ($i = 0; $i < 26; $i++) {
    print $result[$i], "\n";
}