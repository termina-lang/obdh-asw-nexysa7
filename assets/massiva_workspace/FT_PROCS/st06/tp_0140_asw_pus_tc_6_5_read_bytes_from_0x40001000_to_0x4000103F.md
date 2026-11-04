
# TP_0140_ASW_PUS_TC_6_5_READ_BYTES_FROM_0x40001000_TO_0x4000103F

The test checks that telecommand TC(6,5) to read 64 bytes from memory address
0x40001000 to 0x4000103F is executed correctly and the TM (6,6) with the
expected data is received.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,5) to read bytes from memory address 0x40001000 | | TC(6,5) | N = 1, Memory ID = 0, Start Address = 0x40001000, Length = 0x40 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that memory read is executed and TM (6,6) contains expected data | | TM(1,1)<br>TM(6,6)<br>TM(1,7) | N = 1, Memory ID = 0, Start Address = 0x40001000, Length = 64, Read Data = [03100000 .. 01000000] |