/* Based on: http://www.jamesmolloy.co.uk/tutorial_html/1.-Environment%20setup.html */

SECTIONS
{
  .text 0x09000 :
  {
    code = .; _code = .; __code = .;
    *(.text)
    /*. = ALIGN(4096);*/
  }

  .data :
  {
     data = .; _data = .; __data = .;
     *(.data)
     *(.rodata)
     /*. = ALIGN(4096);*/
  }

  .bss :
  {
    bss = .; _bss = .; __bss = .;
    *(.bss)
    /*. = ALIGN(4096);*/
  }

  end = .; _end = .; __end = .;
} 
