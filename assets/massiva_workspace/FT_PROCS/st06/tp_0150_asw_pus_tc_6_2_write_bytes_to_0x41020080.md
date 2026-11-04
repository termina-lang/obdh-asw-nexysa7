
# TP_0150_ASW_PUS_TC_6_2_WRITE_BYTES_TO_0x41020080

The test checks that telecommand TC(6,2) writes specific data to memory address
0x41020080, and then TC(6,5) reads back the data to verify the write operation
was successful.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,2) to write bytes to memory address 0x41020080 | | TC(6,2) | N = 1, Memory ID = 1, Start Address = 0x41020080, Length = 24, Data to write = [BEBACAFE .. F709CA34] |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (1,7) | | TM(1,1)<br>TM(1,7) | N/A |
| **TO + 2** | **STEP1** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,5) to read bytes from memory address 0x41020080 | | TC(6,5) | N = 1, Memory ID = 1, Start Address = 0x41020080, Length = 24 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that memory read returns the previously written data | | TM(1,1)<br>TM(6,6)<br>TM(1,7) | N = 1, Memory ID = 1, Start Address = 0x41020080, Length = 24, ReadData = [BEBACAFE .. F709CA34] |