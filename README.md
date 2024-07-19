# thmenu
Thmenu is a small external cheat menu for Geometry Dash.

# Acquiring the Executable
Ideally, you should use the [latest release](https://github.com/mxtlrr/thmenu/releases),
but if you want to get bleeding edge then you should compile the program yourself:

##
You can use `w64devkit` to compile, just
[download it here](https://github.com/skeeto/w64devkit) and you can run the following commands
```sh
make           # Build thmenu/ itself.
make -C tools/ # Build the tools to help you with tmenu (configuring, etc.)
```

# Roadmap 
- [X] Global keybindings
- [ ] Tons of hacks (see below)
- [ ] Better UI
- [ ] Tools
  - [ ] `genconfig`
  - [ ] `readconfig`

## Hacks to add
- [X] Noclip
- [X] X-position freezing ([#2](https://github.com/mxtlrr/thmenu/issues/2))
- [X] AC Bypass
- [X] Instant complete
- [ ] Speedhack
- [ ] Icon unlock

# Usage
See [CONFIG.md](./CONFIG.md) for configuration. To toggle,
just press the key you configured. You can use the binaries in `tools/` to help configure thmenu.