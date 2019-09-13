# rrBindings

This Repository adds Type safety and autocompletion to the RoyalRender NodeJS Addon.

## Usage

### IMPORTANT
 *  There is Currently only rrBindings support for Node version 6.xx.x (Node 6.17.1 was the last Node 6 release)
 *  For Linux you have to first mount your RoyalRender Server to a local folder before trying to install rrBindings.
 *  For Windows you do not have to escape the backslash when using `npm install`
 *  Do not `npm install` rrBindings with the `--save` flag. This will probably lead to errors when using `npm install` again (at least on Windows when node saves an UNC path in the package.json as a dependency)
 *  In the folder `[RR]/bin/lx64/lib/` you have to rename the `*.node.1.0.0` file to `libNodeJs6_RR.node`
 *  In the folder `[RR]/bin/win64/` you have to rename the `*.node` file to `NodeJs6_RR.node`
 
### Steps to get started
1. Download this repo
2. Place the `package.json` file from `[REPO]/lx64/lib` into `[RR]/bin/lx64/lib/`
3. Place the `package.json` file from `[REPO]/win64/` into `[RR]/bin/win64/`
4. Copy the `nodeJS/` folder from `[REPO]/` into `[RR]/bin/`
5. Copy the example project from `[REPO]/` into the destination you want.
6. `cd` into the example project.
7. Run `npm install`
8. Run`npm install [RR]/bin/nodeJS/<OS YOU USE>/<NODE VERSION YOU USE>`
9. Run `npm start`

### Documentation
For each version of rrTypings, you can find a markdown and a html documentation in the `nodeJS/<OS>/<NODE VERSION YOU USE>/docs` folder.
The Markdown version is directly accessible from this git repository: [Example for win64-v6-docs](nodeJS/win64/v6/docs/md/README.md).
It is pretty handy if you don't know exactly which methods are actually available from the rrBindings.

## Development

If you want to develop this project a bit further, make sure that you have this Folder Structure with exactly those files (you have to configure rrBindings/lx64 and rrBindings/win64 manually) which you can get from [RR]/bin/<OS>/
    
```
rrBindings/
    └─── lx64/
    │     └─── lib/
    │          │─── libNodeJs6_RR.node
    │          │─── libQtCore.so.4
    │          │─── librrShared.so.1
    │          └─── package.json
    └─── win64/
    │     │─── msvcp120.dll
    │     │─── msvcr120.dll
    │     │─── nodeJs6_RR.node
    │     │─── package.json
    │     │─── QtCore4.dll
    │     └─── rrShared.dll
    │
    ├─── nodeJS/
    │   ├─── lx64/
    │   │   └───v6/
    │   │       └─── <files...>
    │   │
    │   └─── win64
    │       └───v6
    │           └─── <files...>
    │
    └─── rrExample
       │─── backpack.config.js
       │─── package.json
       │─── tsconfig.json
       └─── src
             └─── index.ts
```
## Contribution
If you find a bug, something is missing or you know a better way to implement rrBindings, feel free to submit any Pull Requests or issues.