/*
 * Copyright (c) 2008-2010, Regents of the University of California
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * - Neither the name of the University of California, Berkeley nor the names
 *   of its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * ATMEL DataFlash Memory (dfmem) Interface
 *
 * by Fernando L. Garcia Bermudez
 *
 * v.beta
 *
 * Revisions:
 *  Fernando L. Garcia Bermudez 2008-7-23   Initial release
 *                              2010-7-19   Blocking read/writes tested
 *  Stanley S. Baek             2010-8-30   Added buffer read/writes and sector
 *                                          erase for improving writing speeds.
 *
 * Notes:
 *  - Uses an SPI port for communicating with the memory chip.
 */

#include "p33Fxxxx.h"
#include "spi.h"
#include "dfmem.h"


#if (defined(__IMAGEPROC1) || defined(__IMAGEPROC2) || defined(__MIKRO) || defined(__EXP16DEV))
// MIKRO & EXP16DEV has no FLASHMEM, but needs this for compile

    // SPIx pins
    #define SPI_CS          _LATG9

    // SPIx Registers
    #define SPI_BUF         SPI2BUF
    #define SPI_CON1        SPI2CON1
    #define SPI_CON2        SPI2CON2
    #define SPI_STAT        SPI2STAT
    #define SPI_STATbits    SPI2STATbits

#endif

// Commands
#define WRITE_PAGE_VIA_BUFFER1              0x82
#define WRITE_PAGE_VIA_BUFFER2              0x85
#define WRITE_TO_BUFFER1                    0x84
#define WRITE_TO_BUFFER2                    0x87
#define WRITE_BUFFER1_TO_PAGE_NO_ERASE      0x88
#define WRITE_BUFFER2_TO_PAGE_NO_ERASE      0x89
#define WRITE_BUFFER1_TO_PAGE_WITH_ERASE    0x83
#define WRITE_BUFFER2_TO_PAGE_WITH_ERASE    0x86

#define READ_PAGE                           0xD2
#define READ_PAGE_TO_BUFFER_1               0x53
#define READ_PAGE_TO_BUFFER_2               0x55

#define ERASE_PAGE      0x81
#define ERASE_BLOCK     0x50
#define ERASE_SECTOR    0x7C

/*-----------------------------------------------------------------------------
 *          Private variables
-----------------------------------------------------------------------------*/

union {
    unsigned long address;
    unsigned char chr_addr[4];
} MemAddr;


/*----------------------------------------------------------------------------
 *          Declaration of private functions
 ---------------------------------------------------------------------------*/

static inline unsigned char dfmemExchangeByte (unsigned char byte);
static inline void dfmemWriteByte (unsigned char byte);
static inline unsigned char dfmemReadByte (void);
static inline void dfmemSelectChip(void);
static inline void dfmemDeselectChip(void);
static void dfmemSetupPeripheral(void);


/*-----------------------------------------------------------------------------
 *          Public functions
-----------------------------------------------------------------------------*/

void dfmemSetup(void)
{
    dfmemSetupPeripheral();
    dfmemDeselectChip();
}

void dfmemWrite (unsigned char *data, unsigned int length, unsigned int page,
        unsigned int byte, unsigned char buffer)
{
    unsigned char command;
    
    while(!dfmemIsReady());

    // Choose command dependent on buffer choice
    if (buffer == 1) {
        command = WRITE_PAGE_VIA_BUFFER1;
    } else {
        command = WRITE_PAGE_VIA_BUFFER2;
    }
    
    // Restructure page/byte addressing
    // 1 don't care bit + 13 page address bits + 10 byte address bits
    MemAddr.address = (((unsigned long)page) << 10) + byte;


    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(command);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    while (length--) { dfmemWriteByte(*data++); }

    dfmemDeselectChip();
}

void dfmemWriteBuffer (unsigned char *data, unsigned int length, 
        unsigned int byte, unsigned char buffer)
{
    unsigned char command;

    // Choose command dependent on buffer choice
    if (buffer == 1) {
        command = WRITE_TO_BUFFER1;
    } else {
        command = WRITE_TO_BUFFER2;
    }
    
    // Restructure page/byte addressing
    // 14 don't care bit + 10 byte address bits
    MemAddr.address = (unsigned long)byte;
    
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(command);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    while (length--) { dfmemWriteByte(*data++); }

    dfmemDeselectChip();
}

void dfmemWriteBuffer2MemoryNoErase (unsigned int page, unsigned char buffer)
{
    unsigned char command;
    
    while(!dfmemIsReady());

    // Choose command dependent on buffer choice
    if (buffer == 1) {
        command = WRITE_BUFFER1_TO_PAGE_NO_ERASE;
    } else {
        command = WRITE_BUFFER2_TO_PAGE_NO_ERASE;
    }
    
    // Restructure page/byte addressing
    // 1 don't care bit + 13 page address bits + 10 don't care
    MemAddr.address = ((unsigned long)page) << 10;
   
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(command);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    dfmemDeselectChip();
}

void dfmemPush (unsigned char *data, unsigned int length, unsigned int page_reset) 
{
    static unsigned int page = 0;
    static unsigned int byte = 0;
    static unsigned char buffer = 0;

    if (page_reset != 0xffff) {
        page = page_reset;
    }

    if (length > 512 || length == 0) return;

    if (length + byte > 512) {
        dfmemWriteBuffer2MemoryNoErase(page++, buffer);
        buffer ^= 0x01; // toggle buffer
        byte = 0;
    }

    dfmemWriteBuffer(data, length, byte, buffer);
    byte += length;

}

void dfmemRead (unsigned int page, unsigned int byte, unsigned int length,
        unsigned char *data)
{
    while(!dfmemIsReady());

    // Restructure page/byte addressing
    // 1 don't care bit + 13 page address bits + 10 byte address bits
    MemAddr.address = (((unsigned long)page) << 10) + byte;
   
    // Read data from memory
    dfmemSelectChip();
    
    dfmemWriteByte(READ_PAGE);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);
    
    dfmemWriteByte(0x00); // 4 don't care bytes
    dfmemWriteByte(0x00);
    dfmemWriteByte(0x00);
    dfmemWriteByte(0x00);

    while (length--) { *data++ = dfmemReadByte(); }

    dfmemDeselectChip();
}

void dfmemReadPage2Buffer (unsigned int page, unsigned char buffer)
{
    unsigned char command;
    
    while(!dfmemIsReady());

    // Choose command dependent on buffer choice
    if (buffer == 1) {
        command = READ_PAGE_TO_BUFFER_1;
    } else {
        command = READ_PAGE_TO_BUFFER_2;
    }

    // 1 don't care bit + 13 page address bits + 10 don't care bits
    MemAddr.address = ((unsigned long)page) << 10;
    
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(command);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    dfmemDeselectChip();
}

void dfmemErasePage (unsigned int page) 
{ 
    while(!dfmemIsReady());

    // Restructure page/byte addressing
    MemAddr.address = ((unsigned long)page) << 10;
    
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(ERASE_PAGE);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    dfmemDeselectChip();
}

void dfmemEraseBlock (unsigned int page) 
{ 
    while(!dfmemIsReady());

    // Restructure page/byte addressing
    MemAddr.address = ((unsigned long)page) << 10;
    
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(ERASE_BLOCK);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    dfmemDeselectChip();
}

void dfmemEraseSector (unsigned int page) 
{
    while(!dfmemIsReady());

    // Restructure page/byte addressing
    MemAddr.address = ((unsigned long)page) << 10;
    
    // Write data to memory
    dfmemSelectChip();

    dfmemWriteByte(ERASE_SECTOR);
    dfmemWriteByte(MemAddr.chr_addr[2]);
    dfmemWriteByte(MemAddr.chr_addr[1]);
    dfmemWriteByte(MemAddr.chr_addr[0]);

    dfmemDeselectChip();
}

void dfmemEraseChip (void)
{
    while(!dfmemIsReady());
        
    dfmemSelectChip();
    
    dfmemWriteByte(0xC7);
    dfmemWriteByte(0x94);
    dfmemWriteByte(0x80);
    dfmemWriteByte(0x9A);
    
    dfmemDeselectChip();
}

unsigned char dfmemIsReady (void)
{   
    return (dfmemGetStatus() >> 7);
}

unsigned char dfmemGetStatus (void)
{   
    unsigned char byte;    
    
    dfmemSelectChip();
    
    dfmemWriteByte(0xD7);
    byte = dfmemReadByte();
    
    dfmemDeselectChip();

    return byte;
}

// The manufacturer and device id command (0x9F) returns 4 bytes normally
// (including info on id, family, density, etc.), but this functions returns
// just the manufacturer id and discards the rest when deselecting the chip.
unsigned char dfmemGetManufacturerID (void)
{   
    unsigned char byte;
    
    dfmemSelectChip();
    
    dfmemWriteByte(0x9F);
    byte = dfmemReadByte();

    dfmemDeselectChip();

    return byte;
}


/*-----------------------------------------------------------------------------
 *          Private functions
-----------------------------------------------------------------------------*/

// Sends a byte to the memory chip and returns the byte read from it
// 
// Parameters   :   byte to send.
// Returns      :   received byte.
static inline unsigned char dfmemExchangeByte (unsigned char byte)
{
    SPI_BUF = byte;
    while(SPI_STATbits.SPITBF);
    while(!SPI_STATbits.SPIRBF);
    SPI_STATbits.SPIROV = 0;    
    return SPI_BUF;
}

// Sends a byte to the memory chip.
//
// It discards the byte it receives when transmitting this one as it should
// not be important and so that it doesn't stay in the received queue.
// 
// Parameters : byte to send.
static inline void dfmemWriteByte (unsigned char byte)
{
    dfmemExchangeByte(byte);
}

// Receives a byte from the memory chip.
//
// It sends a null byte so as to issue the required clock cycles for receiving
// one from the memory.
//
// Returns : received byte.
static inline unsigned char dfmemReadByte (void)
{
    return dfmemExchangeByte(0x00);
}

// Selects the memory chip.
static inline void dfmemSelectChip(void) { SPI_CS = 0; }

// Deselects the memory chip.
static inline void dfmemDeselectChip(void) { SPI_CS = 1; }

// Initializes the SPIx bus for communicating with the memory.
//
// The MCU is the SPI master and the clock isn't continuous.
static void dfmemSetupPeripheral(void)
{
    SPI_CON1 = ENABLE_SCK_PIN & ENABLE_SDO_PIN & SPI_MODE16_OFF & SPI_SMP_OFF &
               SPI_CKE_ON & SLAVE_ENABLE_OFF & CLK_POL_ACTIVE_HIGH &
               MASTER_ENABLE_ON & PRI_PRESCAL_1_1 & SEC_PRESCAL_4_1;
    SPI_CON2 = FRAME_ENABLE_OFF & FRAME_SYNC_OUTPUT & FRAME_POL_ACTIVE_HIGH &
               FRAME_SYNC_EDGE_PRECEDE;
    SPI_STAT = SPI_ENABLE & SPI_IDLE_CON & SPI_RX_OVFLOW_CLR;
}
