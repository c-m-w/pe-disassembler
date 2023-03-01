# pe-disassembler

A library to gather information about a (32-bit) PE file.

## Example output

For the test PE made with one export, this is the output from the `example` project in JSON format:

<details>
<summary>Output</summary>

```json
{
    "data": {
        "exports": [
            {
                "name": "?add@@YAHHH@Z",
                "rva": 4096
            }
        ],
        "imports": [
            {
                "list": [
                    "MessageBoxW"
                ],
                "module": "USER32.dll"
            },
            {
                "list": [
                    "memset",
                    "_except_handler4_common",
                    "__std_type_info_destroy_list"
                ],
                "module": "VCRUNTIME140.dll"
            },
            {
                "list": [
                    "_seh_filter_dll",
                    "_initterm_e",
                    "_initterm",
                    "_initialize_narrow_environment",
                    "_initialize_onexit_table",
                    "_cexit",
                    "_configure_narrow_argv",
                    "_execute_onexit_table"
                ],
                "module": "api-ms-win-crt-runtime-l1-1-0.dll"
            },
            {
                "list": [
                    "GetCurrentProcessId",
                    "IsDebuggerPresent",
                    "InitializeSListHead",
                    "GetSystemTimeAsFileTime",
                    "GetCurrentThreadId",
                    "UnhandledExceptionFilter",
                    "QueryPerformanceCounter",
                    "IsProcessorFeaturePresent",
                    "TerminateProcess",
                    "GetCurrentProcess",
                    "SetUnhandledExceptionFilter"
                ],
                "module": "KERNEL32.dll"
            }
        ],
        "nt": {
            "build_time": "Wed Jan  4 13:44:14 2023\n",
            "entry_point": 4996,
            "image_base": 268435456,
            "image_size": 24576
        },
        "relocations": [
            {
                "entries": 138,
                "rva": 4096
            },
            {
                "entries": 16,
                "rva": 8192
            }
        ],
        "sections": [
            {
                "name": ".text",
                "rva": 4096,
                "size": 3584
            },
            {
                "name": ".rdata",
                "rva": 8192,
                "size": 2560
            },
            {
                "name": ".data",
                "rva": 12288,
                "size": 512
            },
            {
                "name": ".rsrc",
                "rva": 16384,
                "size": 512
            },
            {
                "name": ".reloc",
                "rva": 20480,
                "size": 512
            }
        ]
    },
    "success": true
}
```
</details>

## Usage

To use the disassembler, construct a `pe` object and use its member functions:

```c++
    // data is pointer to raw PE data
    // size is the size of the PE

    auto mb = pe(data, size);
    auto dos = mb.get_dos();
    auto nt = mb.get_nt();

    auto dir = nt.get_directory<T>();
    ...
```

The object `dir` is an iterator for the types the template accepts. See `example/source/example.cpp` for details. The `pe` constructor can throw two exceptions: `bad_pe` if the raw data pointer is not a PE file, or `bad_architecture` if the PE is not 32-bit:

```c++
    try
    {
        auto mb = pe(data, size);
    }
    catch(bad_pe & e) { }
    catch(bad_architexture & e) { }
```



# Directory index

## example/

Visual studio project to demo features.

## pe disassembler/

Source for the `pe` class and subclasses, which do the disassembling.

## unix/

Build files for compiling on unix systems. The `serialize.cpp` source file takes in a file argument and spits out all of the PE data in JSON format. It catches any exceptions (invalid PE file, invalid architecture) and reports the error if encountered.
