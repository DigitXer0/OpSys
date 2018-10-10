#include "console.h"
    
extern struct Superblock sb;
void sweet(){
    disk_read_sector(2, &sb);
    disk_read_sector(3, ((char*)&sb) + 512);

    kprintf("Volume Label: %s  Free: %u\nBlocks per group: %u  Total blocks: %u\n",
            sb.volname, sb.free_block_count, sb.blocks_per_group, sb.block_count);

    for(int i = 0; i < 3; ++i)
    {        
        kprintf("Reading BDGT from group %d\n", i);
        kprintf("Size of blocks_per_group %u\n\n", sb.blocks_per_group);
        foo((sb.blocks_per_group * i) + 1);
    }

}