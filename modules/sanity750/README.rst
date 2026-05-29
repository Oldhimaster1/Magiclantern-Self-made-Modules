750D Dev Sanity Module (sanity750)
=================================

Purpose
-------
A conservative first Magic Lantern module intended for safe bring-up and
workflow validation on EOS 750D / Rebel T6i development setups.

This repository is an overlay-style module source repository, not a full
Magic Lantern source tree. Copy or place this module directory into the current
active Magic Lantern development tree before building.

Recommended upstream base
-------------------------
Use the current Git-based Magic Lantern development tree:

- ``reticulatedpines/magiclantern_simplified``

Expected placement
------------------
Place this folder inside the upstream ML tree as:

::

    modules/sanity750/

Features (v0.1)
---------------
- Run 750D sanity check
- Show last result
- Reset sanity counters
- Log to file toggle placeholder

Persistent config keys
----------------------
- ``sanity.run_count``
- ``sanity.last_status``
- ``sanity.log_to_file``

Safety profile
--------------
This module intentionally stays in low-risk territory:

- Menu entries
- Persistent config values
- Console output
- Separate task launch pattern

It avoids low-level camera internals, video pipeline hooks, and risky persistent
property writes.

Build
-----
From inside a full Magic Lantern source tree, use the normal module build flow.
For example:

::

    cd modules/sanity750
    make

Or build from the ML root/module build workflow used by your chosen tree.

Deploy
------
Copy the resulting ``.mo`` file to:

::

    ML/MODULES/

Enable the module from the Magic Lantern Modules menu, then restart the camera
so the module loads.

Target
------
Intended for early development workflow testing on EOS 750D / Rebel T6i.
Use a known-good firmware baseline and test conservatively.

Notes
-----
The included GitHub Actions workflow validates repository structure and archives
module sources, but does not perform a real Magic Lantern compile by itself.
A real compile requires the full upstream ML source tree.
