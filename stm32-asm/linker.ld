
ENTRY(reset_handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY {
	RAM		(xrw):	ORIGIN = 0x20000000,	LENGTH = 128K
	FLASH	(xr):	ORIGIN = 0x8000000,		LENGTH = 512K
}

SECTIONS {
	.text : {
		KEEP(*(.text.reset_handler))
	} > FLASH

	stack(NOLOAD) : {
		. += 1K;
	} > RAM
}
