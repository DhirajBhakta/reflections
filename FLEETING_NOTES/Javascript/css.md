## display:
- inline
- inline-block
- block
![](https://pbs.twimg.com/media/EdOQGgTXgAE5QdB.jpg)
### inline
elements run on the same line, you cannot change height and width

### inline-block
elements run on the same line, you CAN change height and width

### block
elements start from new line


## position
- relative
- absolute
- fixed

### relative
_"relative to itself"_
- useless without top, left, right, bottom attrs
- gives the power of z-index
- limits scope of **absolute** children
    - any child of relative div can be absolutely positioned within that parent.

### absolute
- useless without top, left, right, bottom attrs
- will be within the scope of the immediate parent with relative or absolute positioning....else defaults to html parent
![](https://i2.wp.com/css-tricks.com/wp-content/uploads/2020/07/Screen-Shot-2020-07-24-at-11.46.02-AM.png?resize=1000%2C648&ssl=1)

### fixed
fixed w.r.t to the viewport.
Scroll and its still in the same place!



# Resources
https://www.freecodecamp.org/news/the-css-handbook-a-handy-guide-to-css-for-developers-b56695917d11/



