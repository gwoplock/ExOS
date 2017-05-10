/*
 * PageTable.cpp
 *
 *  Created on: Mar 2, 2017
 *      Author: garrett
 */

#include "PageTable.h"

PageTable::PageTable( ) {
}
PageTable::PageTable(bool buildFlag) {
	buildFlag = !buildFlag;
	for (int i = 0; i < 1024; i++) {
		pageDir[i].present = 0;
		pageDir[i].pageTableAddr = ( (uint32_t)( &pageTables[i * 1024])
				- vKernelStart) >> 12;
	}
	size_t kernelPages = ( ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart - vKernelStart) / fourKb + 1);
	size_t kernelDirs = (kernelPages / 1024) + 1;
	for (size_t i = 0; i < kernelDirs; i++) {
		pageDir[KernelPageDirStart + i].present = 1;
		pageDir[KernelPageDirStart + i].writeThrough = 1;
		pageDir[KernelPageDirStart + i].user_super = 1;
		pageDir[KernelPageDirStart + i].read_write = 1;
	}
	for (size_t i = 0; i < kernelPages; i++) {
		pageTables[KernelPageStart + i].read_write = 1;
		pageTables[KernelPageStart + i].user_super = 0;
		pageTables[KernelPageStart + i].writeThrough = 1;
		pageTables[KernelPageStart + i].present = 1;
		pageTables[KernelPageStart + i].physicalAddress = i;
		pageTables[KernelPageStart + i].global = 1;
	}
	movePageTable(pageDir);
}
void* PageTable::page(void* phyStart, void* virtStart, size_t size) {
	size_t sizeInPages = (size / fourKb)
			+ ( ( ( ((uint32_t) size) & 0xFFF) != 0)
					|| ( ( ((uint32_t) phyStart) & 0xFFF) != 0));
	size_t sizeInDirs = sizeInPages = (sizeInPages / 1024) + 1;
	uint32_t startPage = (uint32_t) virtStart / fourKb;
	uint32_t startDir = startPage / 1024;
	for (size_t i = 0; i < sizeInDirs; i++) {
		pageDir[startDir + i].present = 1;
	}
	for (size_t i = 0; i < sizeInPages; i++) {
		pageTables[startPage + i].present = 1;
		pageTables[startPage + i].global = 1;
		pageTables[startPage + i].physicalAddress = ((uint32_t) phyStart
				+ (i * fourKb)) >> 12;
	}
	return (void*) ( ((uint32_t) virtStart & ~0xFFF)
			| ((uint32_t) phyStart & 0xFFF));
}
void PageTable::movePageTable(PageDirEntry pageDir[1024]) {
	asm volatile ("mov %0, %%eax;"
			"mov %%eax, %%cr3":: "r" (pageDir):"%eax");
}

void PageTable::build(){
	for (int i = 0; i < 1024; i++) {
		pageDir[i].present = 0;
		pageDir[i].pageTableAddr = ( (uint32_t)( &pageTables[i * 1024])
				- vKernelStart) >> 12;
	}
	size_t kernelPages = ( ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart - vKernelStart) / fourKb + 1);
	size_t kernelDirs = (kernelPages / 1024) + 1;
	for (size_t i = 0; i < kernelDirs; i++) {
		pageDir[KernelPageDirStart + i].present = 1;
		pageDir[KernelPageDirStart + i].writeThrough = 1;
		pageDir[KernelPageDirStart + i].user_super = 1;
		pageDir[KernelPageDirStart + i].read_write = 1;
	}
	for (size_t i = 0; i < kernelPages; i++) {
		pageTables[KernelPageStart + i].read_write = 1;
		pageTables[KernelPageStart + i].user_super = 0;
		pageTables[KernelPageStart + i].writeThrough = 1;
		pageTables[KernelPageStart + i].present = 1;
		pageTables[KernelPageStart + i].physicalAddress = i;
		pageTables[KernelPageStart + i].global = 1;
	}
	movePageTable((PageDirEntry*)((uint32_t)pageDir - vKernelStart));
}
