# How to configure THMenu
THMenu has global keybindings, so that:
- You don't have to tab out of GD
- It mimics what internal cheats do.

However there are some drawbacks, notably that you can't use those
keys in other applications. To configure, just change the
hex values. For example, if I want J to be noclip and F to be
x-pos freeze then my config file would be
```
0x4A,0x46
```

**Make sure there are NO SPACES!**

## Limitations
The only keys that have been defined as of v0.1 are:
- The 0 through 9 keys (not numpad)
- A through Z

You can see what the hex codes are at
[this](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes) URL.

## The `keys.cfg` file

### Default Entries
|  Key  | Corresponds To |   Function   |
| ----  | -------------- | ------------ | 
|`0x41` | The A key      | Noclip       |
|`0x46` | The F key      | X-Pos Freeze |

```c
0x41,0x46
```