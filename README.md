# Malbolge Virtual Machine

Interpreter for the Malbolge Virtual Machine with a machine width of 10.

Unlike the reference implementation, this implementation does not rely on dynamic memory allocation.

## Compilation
`make malbolge-vm` or `cc malbolge-vm.c -o malbolge-vm`

## Usage
`malbolge-vm [file].mb`

## Examples
Hello World:	`malbolge-vm HelloWorld.mb`

cat:		`malbolge-vm cat.mb`

## License
MIT or dedicated to the public domain if applicable.
