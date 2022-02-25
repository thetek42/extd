# ExtD

ExtD is a markup language similar to Markdown. This implementation compiles
ExtD code into HTML.

## Compiling and Running

Dependencies:
- GCC (other compilers should also work, though)

```console
$ git clone https://github.com/thetek42/extd
$ cd etxd
$ make
```

The compiled binary will be located in `bin/extd`.

## Usage

You can compile a .extd file by running `extd <file>`. The output file will be
determined based on the input, unless an output has been specified using `-o`:
`extd <input> -o <output>`. Themes can be selected with the `-t` option: `extd
<file> -t <theme>`. The theme can either be a builtin theme (currently, only
'default' is available) or a path to a file.

## Examples

Examples can be found in the `examples/` folder.

