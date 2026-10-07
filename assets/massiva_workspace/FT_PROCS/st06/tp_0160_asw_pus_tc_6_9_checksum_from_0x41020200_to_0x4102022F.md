
# TP_0160_ASW_PUS_TC_6_9_CHECKSUM_FROM_0x41020200_TO_0x4102022F

The test writes 48 known bytes to memory addresses 0x41020200 to 0x4102022F
with TC(6,2), and then checks that telecommand TC(6,9) calculates their
checksum and that the TM (6,10) carries the expected value 0x5D6E.

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,2) to write 48 known bytes to memory address 0x41020200 | | TC(6,2) | N = 1, Memory ID = 1, Start Address = 0x20200, Length = 48, Data to write = [40414243 .. 6C6D6E6F] |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the received sequence is TM (1,1), TM (1,7) | | TM(1,1)<br>TM(1,7) | N/A |
| **TO + 2** | **STEP1** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,9) to calculate the checksum of 48 bytes from memory address 0x41020200 | | TC(6,9) | N = 1, Memory ID = 1, Start Address = 0x20200, Length = 48 |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that checksum calculation is executed and TM (6,10) contains expected checksum | | TM(1,1)<br>TM(6,10)<br>TM(1,7) | N = 1, Memory ID = 1, Start Address = 0x20200, Length = 48, Checksum = 0x5D6E |
