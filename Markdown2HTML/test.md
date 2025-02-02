
# Markdown Renderer Test File

This file tests various Markdown syntax elements and edge cases.

---

## Headers
# H1 Header
## H2 Header
### H3 Header
#### H4 Header
##### H5 Header
###### H6 Header
####### Not a header (7 #)

# Header With `Quotes` and [LINKS](github.com)

---

## Emphasis
*italic* _italic_  
**bold** __bold__  
***bold italic*** ___bold italic___  
~~strikethrough~~  
**bold *with italic* inside**  
`code span`

---

## Lists

### Unordered
- Item 1
- Item 2
  - Nested Item 2a
  - Nested Item 2b
    - Double nested Item 2bi
- Item 3

### Ordered
1. First item
2. Second item
3. Third item
   1. Nested ordered
   2. Nested ordered
4. Fourth item

### Mixed
- Unordered
  1. Nested ordered
  2. Nested ordered
- Another unordered
  - Nested unordered
  - Nested unordered

---

## Links & Images
[inline link](http://example.com)  
[reference link][1]  
[empty title link](http://example.com "")  
![image alt text](https://example.com/image.jpg)  
<http://autolink.com>  
<email@example.com>  

[1]: http://example.com "Title"

---

## Code
Inline `code` with backticks.

```python
# Code block
def hello():
    print("Hello World!")
```

    Indented code block
    with multiple lines

`` `Escaped backticks` ``

---

## Blockquotes
> Simple blockquote

> Multi-line
> blockquote

> > Nested
> > blockquote

> **Markdown** inside blockquote
> - List
> - Items

---

## Horizontal Rules
---
***
* * *
- - -
  ---  (with leading spaces)

---

## Tables
| Syntax | Description |
| --- | --- |
| Header | Title |
| Paragraph | Text |

| Left | Center | Right |
| :--- | :---: | ---: |
| 1 | 2 | 3 |
| Long content cell | With `code` | **bold** |

---

## Footnotes
Here's a sentence with a footnote.[^1]  
Another footnote reference.[^2]  

[^1]: First footnote definition  
[^2]: Second footnote  
with multi-line definition

---

## Task Lists
- [x] Completed task
- [ ] Incomplete task
- [X] Capitalized check

---

## HTML
<div style="color: red">HTML block</div>  
Inline HTML: <span style="color: blue">text</span>  
Self-closing: <br/>  
Comment: <!-- hidden -->  

---

## Edge Cases
### Empty Elements
[]()  
![]( )  

### Mixed Formatting
**Bold *with [link](http://example.com) inside***  

### Escaping
\*Not italic\*  
\# Not a header  

### Special Characters
Link with parens: [text](http://example.com/(parens))  
Image with spaces: ![alt](http://example.com/image%20with%20spaces.jpg)

### Code in Headers
# `Header` **with** `code`

### Nested Formatting
> - Blockquote **with**  
>   `code` and [link]()

### Empty Lines Between Elements

Text above
***
Text below

---

## Complex Combination
1. **List item** with [link](http://example.com)
   > Blockquote containing  
   > `code` and _italic_
   
   ```
   Code block
   with multiple lines
   ```
   
   | Table | In |
   |---|---|
   | List | Item |

2. Second item  
   End with hard line break (space)  
