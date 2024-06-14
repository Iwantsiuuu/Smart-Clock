.pushsection command_data, "ax", %progbits
#.incbin "data/Trigger_and_command_pack_withTxt.bin"
.incbin "data/Speech_Smart_Clock_pack_WithTxt.bin"
.popsection

.pushsection license_data, "ax", %progbits
#.incbin "data/EF2F17571896353D1718158130_License.bin"
.incbin "data/F52F2A1F028CAFE41718160741_License.bin"
.popsection
