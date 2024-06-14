.pushsection command_data, "ax", %progbits
.incbin "data/Test_pack_WithTxt.bin"
.popsection

.pushsection license_data, "ax", %progbits
.incbin "data/F52F2A1F028CAFE41718160741_License.bin"
.popsection
