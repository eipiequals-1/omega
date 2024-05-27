# Jam


## Compiling to WASM
Run

`make` to compile and build. The output files will be in __build__

Navigate to __build__.

Run `emrun index.html` to host the live server. You can leave this running for the duration of development.

## Release
To deploy the project, change 

`EMCCFLAGS += --shell-file assets/emscripten/shell-debug.html`

to

`EMCCFLAGS += --shell-file assets/emscripten/shell-release.html`

and rebuild the project. Now, you can package this into a zip file for itch.io or other hosting services.
