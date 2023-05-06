768x576 game area - 64x64 tiles - therefore 12x9 visible tiles

THERE MUST ALWAYS BE 12 CHARACTERS PER ROW - use " "(space character) for no objects
ROW 1 MUST = "============"
ROW 2 - ROW 27 = level obstacles
ROW 28 MUST = "------------"
ROW 29 MUST = "~~~~~~~~~~~~"
ROW 30 MUST = "xxxxxxxxxxxx"

Player spawns above Row 28 in the middle.

case ' ':
{
    // nothing
}
case '-':
{
    // platform
}
case '^':
{
    // trappedPlatform
    DOES NOT ROTATE
}
case '<':
{
    // trappedPlatform
    STARTS NOT ROTATED
}
case '>':
{
    // trappedPlatform
    STARTS ROTATED
}
case 'H':
{
    // trapHorizontal
}
case 'I':
{
    // trapHorizontal
}
case '~':
{
    // destroyedEdge
}
case 'x':
{
    // destroyed
}
case '=':
{
    // exit
}
case '+':
{
    // point
}
