#include <stdio.h> /* printf */
#include <sys/stat.h> /* open */
#include <fcntl.h> /* open */
#include <sys/types.h> /* lseek */
#include <sys/stat.h> /* inode i_mode macro */
#include <unistd.h> /* lseek, read, close */
#include <stdlib.h> /* exit */
#include <errno.h> /* errno */
#include <string.h> /* memcpy */
/*#include </usr/include/linux/fs.h>
#include </usr/src/linux-headers-5.3.0-51/include/linux/ext2_fs.h>*/ /* ext2 structs */

#include "ext2.h"
#include "ext2_fs.h"

static void PrintSuperblock(void *super_block, const char *device_path);
static void PrintGroupDescriptor(void *group_descriptor, const char *device_path);
static void PrintInode(void *bitmap);
static int PrintContents(int fd, struct ext2_inode *inode, unsigned int inode_start, const char *filepath);
static int PrintFileContent(const char *device_path, const char *filepath) {}

static unsigned int block_size = 0;

int EXT2PrintFile(const char *device_path, const char *filepath)
{
    int fd;
    struct ext2_super_block super_block;
    struct ext2_group_desc group_descriptor;
    struct ext2_inode inode;

    unsigned int first_data_block = 0;
    unsigned int root_inode_offset = 0;
    unsigned int first_inode_block_offset = 0;

    fd = open(device_path, O_RDONLY);

    if (-1 == fd)
    {
        printf("error opening device\n");
        printf("errno: %d\n", errno);
        return (1);
    }

    /* move to superblock */
    if ((off_t) -1 == lseek(fd, 1024, SEEK_SET))
    {
        printf("error lseek\n");
        close(fd);
        return (1);
    }

    if (-1 == read(fd, &super_block, sizeof(super_block)))
    {
        printf("error read\n");
        printf("errno: %d\n", errno);
        close(fd);
        return (1);
    }

    if (super_block.s_magic != EXT2_SUPER_MAGIC)
    {
        printf("error, not an ext2 filesystem\n");
        close(fd);
        return (1);
    }

    PrintSuperblock(&super_block, device_path);

    first_data_block = super_block.s_first_data_block;

    block_size = 1024 << super_block.s_log_block_size;

    /* move to group descriptors */
    if ((off_t) -1 == lseek(fd, 1024 + block_size, SEEK_SET))
    {
        printf("error lseek\n");
        printf("errno: %d\n", errno);
        close(fd);
        return (1);
    }

    if (-1 == read(fd, &group_descriptor, sizeof(group_descriptor)))
    {
        printf("error read\n");
        printf("errno: %d\n", errno);
        close(fd);
        return (1);
    }
    
    PrintGroupDescriptor(&group_descriptor, device_path);

    first_inode_block_offset = (group_descriptor.bg_inode_table) * block_size;
    root_inode_offset = (EXT2_ROOT_INO - 1) * sizeof(struct ext2_inode);

    if ((off_t)-1 == lseek(fd, first_inode_block_offset + root_inode_offset, SEEK_SET))
    {
        printf("error lseek\n");
        printf("errno: %d\n", errno);
        close(fd);
        return (1);
    }

    if (-1 == read(fd, &inode, (sizeof(inode))))
    {
        printf("error read\n");
        printf("errno: %d\n", errno);
        close(fd);
        return (1);
    }
    
    PrintInode(&inode);

    printf("Orig: %s\n", filepath);
    PrintContents(fd, &inode, first_inode_block_offset, filepath);
    
    /*PrintFileContent(device_path, filename);
    */

    if (-1 == close(fd))
    {
        printf("error close\n");
        return (1);
    }

    return 0;
}

static void PrintSuperblock(void *super_block, const char *device_path)
{
    struct ext2_super_block *sb = (struct ext2_super_block *)super_block;

    printf("Reading super-block from device %s :\n"
	       "Inodes count            : %u\n"
	       "Blocks count            : %u\n"
	       "Reserved blocks count   : %u\n"
	       "Free blocks count       : %u\n"
	       "Free inodes count       : %u\n"
	       "First data block        : %u\n"
	       "Block size              : %u\n"
	       "Blocks per group        : %u\n"
	       "Inodes per group        : %u\n"
	       "Creator OS              : %u\n"
	       "First non-reserved inode: %u\n"
	       "Size of inode structure : %hu\n"
	       ,
           device_path,
	       sb->s_inodes_count,  
	       sb->s_blocks_count,
	       sb->s_r_blocks_count,     /* reserved blocks count */
	       sb->s_free_blocks_count,
	       sb->s_free_inodes_count,
	       sb->s_first_data_block,
	       block_size,
	       sb->s_blocks_per_group,
	       sb->s_inodes_per_group,
	       sb->s_creator_os,
	       sb->s_first_ino,          /* first non-reserved inode */
	       sb->s_inode_size);
}

static void PrintGroupDescriptor(void *group_descriptor, const char *device_path)
{
    struct ext2_group_desc *gd = (struct ext2_group_desc *)group_descriptor;

    printf("Reading first group-descriptor from device %s:\n"
	       "Blocks bitmap block: %u\n"
	       "Inodes bitmap block: %u\n"
	       "Inodes table block : %u\n"
	       "Free blocks count  : %u\n"
	       "Free inodes count  : %u\n"
	       "Directories count  : %u\n"
	       ,
           device_path,
	       gd->bg_block_bitmap,
	       gd->bg_inode_bitmap,
	       gd->bg_inode_table,
	       gd->bg_free_blocks_count,
	       gd->bg_free_inodes_count,
	       gd->bg_used_dirs_count);
}

static void PrintInode(void *inode)
{
    size_t i = 0;
    struct ext2_inode *in = (struct ext2_inode *)inode;

    printf("i_mode: %u\n"
            "i_uid: %u\n"
            "i_size: %u\n"
            "i_atime: %u\n"
            "i_ctime: %u\n"
            "i_mtime: %u\n"
            "i_dtime: %u\n"
            "i_gid: %u\n"
            "i_links_count: %u\n"
            "i_blocks: %u\n"
            "i_flags: %u\n",
            in->i_mode,
            in->i_uid,
            in->i_size,
            in->i_atime,
            in->i_ctime,
            in->i_mtime,
            in->i_dtime,
            in->i_gid,
            in->i_links_count,
            in->i_blocks,
            in->i_flags);

    printf("is directory: %d\n", S_ISDIR(in->i_mode));

    for (i = 0; i < EXT2_N_BLOCKS; ++i)
    {
        if (i < EXT2_NDIR_BLOCKS)                                 /* direct blocks */
            printf("Block %lu : %u\n", i, in->i_block[i]);
        else if (i == EXT2_IND_BLOCK)                             /* single indirect block */
            printf("Single   : %u\n", in->i_block[i]);
        else if (i == EXT2_DIND_BLOCK)                            /* double indirect block */
            printf("Double   : %u\n", in->i_block[i]);
        else if (i == EXT2_TIND_BLOCK)                            /* triple indirect block */
            printf("Triple   : %u\n", in->i_block[i]);
    }
}

static int PrintContents(int fd, struct ext2_inode *inode, unsigned int inode_start, const char *filepath)
{
    void *block = NULL;
    unsigned int mode = inode->i_mode;
    unsigned int file_size = inode->i_size;

    if (*filepath == '/')
    {
        ++filepath;
    }

    if (S_ISREG(mode))
    {
        printf("This is a file\n");
        
        if ((block = malloc(sizeof(file_size))) == NULL)
        {
            printf("malloc\n");
            close(fd);
            return (1);
        }

        if ((off_t)-1 == lseek(fd, inode->i_block[0] * block_size, SEEK_SET))
        {
            printf("lseek\n");
            close(fd);
            return (1);
        }
        
        if (-1 == read(fd, block, file_size))
        {
            printf("read\n");
            close(fd);
            return (1);
        }

        printf("data: %s", block);

        free(block); block = NULL;
        return (0);

    }
    else if (S_ISDIR(mode))
    {
        printf("This is a dir\n");
        struct ext2_dir_entry *entry;
        unsigned int size = 0;
        char *file = malloc(strlen(filepath) + 1);
        char *file_start = file;

        if ((block = malloc(sizeof(block_size))) == NULL)
        {
            printf("malloc");
            close(fd);
            return (1);
        }

        entry = (struct ext2_dir_entry *)block;

        if ((off_t)-1 == lseek(fd, inode->i_block[0] * block_size, SEEK_SET))
        {
            printf("lseek\n");
            close(fd);
            return (1);
        }

        if (-1 == read(fd, block, block_size))
        {
            printf("read\n");
            close(fd);
            return (1);
        }

        while (*filepath != '\0' && *filepath != '/')
        {
            *file = *filepath;
            ++filepath;
            ++file;
        }
        *file = '\0';

        while (size < file_size && entry->inode)
        {
            char filename[EXT2_NAME_LEN + 1];
            struct ext2_inode next_inode;

            memcpy(filename, entry->name, entry->name_len);
            filename[entry->name_len] = '\0';
            printf("inode: %u, filename: %s\n", entry->inode, filename);

            printf("filename: %s, file: %s\n", filename, file_start);
            if (strcmp(filename, file_start) == 0)
            {
                if ((off_t)-1 == lseek(fd, inode_start + ((entry->inode - 1) * sizeof(struct ext2_inode)), SEEK_SET))
                {
                    printf("lseek\n");
                    close(fd);
                    exit(1);
                }

                if (-1 == read(fd, &next_inode, sizeof(struct ext2_inode)))
                {
                    printf("read\n");
                    close(fd);
                    exit(1);
                }

                printf("is dir: %d\n", S_ISDIR(next_inode.i_mode));
                printf("Next: %s\n", filepath);

                if (0 == PrintContents(fd, &next_inode, inode_start, filepath))
                {
                    free(block); block = NULL;
                    return (0);
                }
            }

            entry = (void *)entry + entry->rec_len; 
            size += entry->rec_len;
        }
    }
    else
    {
        printf("Unknown file type\n");
        free(block); block = NULL;
    }

    return (1);
}
