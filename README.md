# Malbolge Virtual Machine

Interpreter for the Malbolge Virtual Machine with a machine width of 10.

Written in ANSI C.

Unlike the reference implementation, this implementation does not rely on dynamic memory allocation for storing the virtual machine's main memory.

The reference implementation can be found at [Malbolge reference impl](https://web.archive.org/web/20211215100624/http://www.lscheffer.com/malbolge_interp.html).

The official specification can be found at [Malbolge spec](https://web.archive.org/web/20220105064105/http://www.lscheffer.com/malbolge_spec.html).

## Compilation
`make malbolge-vm` or `cc malbolge-vm.c -o malbolge-vm`

## Usage
`malbolge-vm [file].mb`

## Examples
Hello World:	`malbolge-vm examples/HelloWorld.mb`

cat:		`malbolge-vm examples/cat.mb`

99 Bottles of Beer:   `malbolge-vm examples/bottles-995.mb`

## License
MIT or dedicated to the public domain if applicable.
