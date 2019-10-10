# oryol-tbui

TurboBadger-UI wrapper module for Oryol (https://github.com/fruxo/turbobadger)

Oryol sample: https://floooh.github.com/oryol-samples/wasm/TurboBadgerDemo.html

### How to integrate into your Oryol project:

First, add a new import to the fips.yml file of your project:

```yaml
imports:
    oryol-tbui:
        git: https://github.com/floooh/oryol-tbui.git
```

Next, add a new dependency 'TBUI' to you app's CMakeLists.txt file:

```cmake
fips_begin_app(MyApp windowed)
    ...
    fips_deps(TBUI)
fips_end_app()
```

Finally, as a special case, you need to add a global header search path
to your toplevel CMakeLists.txt file, this is necessary because TurboBadger
requires a customized config header which needs to show up before 
TurboBadger's own config header file, simply add the following
to you toplevel CMakeLists.txt file, before the fips\_setup():

```cmake
include_directories(../oryol-tbui/src/TBUI/tb)
```

After that, run 'fips gen' as usual to fetch the new dependencies and rebuild
the build files:

```bash
> ./fips gen
```

