#include <stdio.h>
#include <stdint.h>
#include "sd.h"
#include "fat.h"
#include "rprintf.h"
#include "serial.h"
//#include "clibfuncs.h"

struct boot_sector *bs;
char bootSector[512];
char rootSector[512];
//char fat_table[8*SECTOR_SIZE];
struct root_directory_entry *fat;

unsigned int root_sector;

int fatInit(){
	char buffer[10];
	sd_readblock(0, bootSector, 1);
	bs = bootSector;
	int x = 0;

	while (bs->fs_type[x] !=  ' ' || x >= 8){
		esp_printf(putc,"%c", bs->fs_type[x]);
		buffer[x] = bs->fs_type[x];
		x++;
		buffer[x] = 0;
	}
	if(bs->boot_signature = 0xaa55){
		esp_printf(putc, "Validated boot signiture \n");
	}

	if(strcmp(buffer, "FAT16")){
		esp_printf(putc, "It is FAT16 \n \n");
	}

	esp_printf(putc,"Bytes per sector = %d \n" ,bs->bytes_per_sector);
	esp_printf(putc,"Sectors per cluster = %d \n" ,bs->num_sectors_per_cluster);
	esp_printf(putc,"Num Fat Tables = %d \n" ,bs->num_fat_tables);
}

struct file *file_open;
void fatOpen(struct file* file, char* filename){
	int t_sectors = bs->num_root_dir_entries;
	int t = 1;
	char buffer[10];

	int root_sector_value = (bs->num_fat_tables * bs-> num_sectors_per_fat) + bs->num_hidden_sectors + bs->num_reserved_sectors;
	esp_printf(putc,  "BOOT SECTOR = %x\n", bs);
	sd_readblock(root_sector_value, rootSector, 1);
	fat = rootSector;
	while(t < t_sectors ) {
	int i = 0;
	while (i < 8){
		esp_printf(putc, "%c", fat->file_name[i]);
		if(fat -> file_name[i] != ' ')
			buffer[i] = fat->file_name[i];
		i++;
	}
	buffer[7] = 0;
	if (strcmp(buffer, filename) == 0){
		esp_printf(putc, "Buffer is equal \n");	
		file->rde = *fat;
		file->start_cluster = fat->cluster;
		return;	
		}
		esp_printf(putc, "\n%s\n", buffer);
		t++;
		fat++;		
		}
	}


void fatRead(struct file* file, char buffer, int bytesToRead){

	esp_printf(putc, "\nRDE Cluster --> %d \n", file->rde.cluster);

	int first_root_dir = bs->num_reserved_sectors + (bs->num_fat_tables * bs->num_sectors_per_fat) + ((bs->num_root_dir_entries * 32) + (bs->bytes_per_sector - 1)) / bs->bytes_per_sector;
	int first_sector = first_root_dir + ((file->rde.cluster - 2) * bs->num_sectors_per_cluster);

	sd_readblock(first_sector,iBuffer,1);

	esp_printf(putc, "Readblock --> %s\n", iBuffer);
	esp_printf(putc, "First root dir --> %d\n", first_root_dir);
	esp_printf(putc, "First sector --> %d\n", first_sector);
	
}
