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
	//set all page dirs not present and set the addr to the page table.
	for (int i = 0; i < 1024; i++) {
		pageDir[i].present = 0;
		pageDir[i].pageTableAddr = ( (uint32_t)( &pageTables[i * 1024])
				- vKernelStart) >> 12;
	}
	//TODO set all page table entry to not present on dirs that are present
	//calculate the number of pages the kernel takes up
	size_t kernelPages = ( ( (size_t)( &kernelSize) + (uint32_t)
			& kernelStart - vKernelStart) / fourKb + 1);
	//also need the number of pages
	size_t kernelDirs = (kernelPages / 1024) + 1;
	//for every dir that we need mark it as present, and a few other things
	for (size_t i = 0; i < kernelDirs; i++) {
		pageDir[KERNEL_PAGE_DIR_START + i].present = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].writeThrough = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].userSuper = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].readWrite = 1;
	}
	//for each page set the props
	for (size_t i = 0; i < kernelPages; i++) {
		pageTables[KERNEL_PAGE_START + i].readWrite = 1;
		pageTables[KERNEL_PAGE_START + i].userSuper = 0;
		pageTables[KERNEL_PAGE_START + i].writeThrough = 1;
		pageTables[KERNEL_PAGE_START + i].present = 1;
		pageTables[KERNEL_PAGE_START + i].physicalAddress = i;
		pageTables[KERNEL_PAGE_START + i].global = 1;
	}
	//change the page dir were using
	movePageTable(pageDir);
}
/**
 * page in some mem
 * @param phy Start
 * @param virt Start
 * @param size to page
 * @return the actual start point
 */
//TODO check if already paged in, if so return error
void* PageTable::page(void* phyStart, void* virtStart, size_t size) {
	//convert from bytes to 4Kb pages
	size_t sizeInPages = (size / fourKb)
			+ ( ( ( ((uint32_t) size) & 0xFFF) != 0)
					|| ( ( ((uint32_t) phyStart) & 0xFFF) != 0));
	//covert to page dirs
	size_t sizeInDirs = sizeInPages = (sizeInPages / 1024) + 1;
	//calc the starting points
	uint32_t startPage = (uint32_t) virtStart / fourKb;
	uint32_t startDir = startPage / 1024;
	//set the dirs present
	//TODO add options for different flags
	for (size_t i = 0; i < sizeInDirs; i++) {
		pageDir[startDir + i].present = 1;
	}
	//dito for the page tables
	for (size_t i = 0; i < sizeInPages; i++) {
		pageTables[startPage + i].present = 1;
		pageTables[startPage + i].global = 1;
		pageTables[startPage + i].physicalAddress = ((uint32_t) phyStart
				+ (i * fourKb)) >> 12;
	}
	//return the starting point
	return (void*) ( ((uint32_t) virtStart & ~0xFFF)
			| ((uint32_t) phyStart & 0xFFF));
}
/**
 * asm helper to move the page dir
 * @param page Dir
 */
void PageTable::movePageTable(PageDirEntry pageDir[1024]) {
	asm volatile ("mov %0, %%eax;"
			"mov %%eax, %%cr3":: "r" (pageDir):"%eax");
}
//TODO move above to here
/**
 * resetup paging, set it how I like it
 */
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
		pageDir[KERNEL_PAGE_DIR_START + i].present = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].writeThrough = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].userSuper = 1;
		pageDir[KERNEL_PAGE_DIR_START + i].readWrite = 1;
	}
	for (size_t i = 0; i < kernelPages; i++) {
		pageTables[KERNEL_PAGE_START + i].readWrite = 1;
		pageTables[KERNEL_PAGE_START + i].userSuper = 0;
		pageTables[KERNEL_PAGE_START + i].writeThrough = 1;
		pageTables[KERNEL_PAGE_START + i].present = 1;
		pageTables[KERNEL_PAGE_START + i].physicalAddress = i;
		pageTables[KERNEL_PAGE_START + i].global = 1;
	}
	movePageTable((PageDirEntry*)((uint32_t)pageDir - vKernelStart));
}
