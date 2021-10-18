extern void load_page_directory();
extern void enable_paging();

unsigned int *page_directory;

void paging_init();

int create_page_entry( int, char, char, char, char, char, char, char, char );
