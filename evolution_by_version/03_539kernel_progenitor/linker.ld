/* Based on: http://www.jamesmolloy.co.uk/tutorial_html/1.-Environment%20setup.html */

SECTIONS
{
  .text 0x09000 :
  {
    code = .; _code = .; __code = .;
    *(.text)
  }

  .data :
  {
     data = .; _data = .; __data = .;
     *(.data)
     *(.rodata)
  }

  .bss :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
  }

  end = .; _end = .; __end = .;
} 
