
# TP_0180_ASW_PUS_TC_6_2_REJECT_WRITE_BYTES_TO_READ_ONLY_MEMORY

The test checks that telecommand TC(6,2) attempting to write to read-only memory
is effectively rejected and the TM (1,1) and TM (1,4) are received with error
code 9 (write to read-only memory).

| STEPS | | | | |
|-------|-|-|-|-|
| **TO + 1** | **STEP0** | | | |
| | | **INPUTS** | **TC** | **App Data** |
| | Send the TC (6,2) to attempt writing to read-only memory | | TC(6,2) | N = 1, Memory ID = 0, Start Address = 0x40000100, Length = 24, Data to Write = [BEBACAFE .. F709CA34] |
| | | **OUTPUTS** | **TM** | **App Data Filter** |
| | Check that the telecommand is rejected and the TM (1,1) and TM (1,4) telemetry packets are received with error code 9 | | TM(1,1)<br>TM(1,4) | Error Code = 9, Memory ID = 0x00 |