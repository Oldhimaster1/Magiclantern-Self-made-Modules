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
Use the current Git-based Magic Lantern development tree::

    reticulatedpines/magiclantern_simplified

Expected repository layout
--------------------------
This overlay repository mirrors a fragment of the upstream ML tree::

    modules/
      sanity750/
        README.rst
        sanity750.c
        Makefile

Expected placement inside upstream ML tree
------------------------------------------
Place this folder inside the upstream ML tree as::

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
For example::

    cd modules/sanity750
    make

Or build from the ML root / module build workflow used by your chosen tree.

Expected output
---------------
The module name is ``san750``, so the built module artifact is expected to be::

    san750.mo

Deploy
------
Copy the resulting ``san750.mo`` file to::

    ML/MODULES/

Enable the module from the Magic Lantern Modules menu, then restart the camera
so the module loads.

Suggested first test procedure
------------------------------
1. Confirm your camera is on a known-good firmware baseline for your ML tree.
2. Build the module inside the full upstream ML source tree.
3. Copy ``san750.mo`` to ``ML/MODULES/`` on the card.
4. Enable the module from the Magic Lantern Modules menu.
5. Restart the camera so the module loads.
6. Open the ML Debug menu and run ``Run 750D sanity check``.
7. Verify that the console displays the status screen and that the run counter
   persists across reloads.

Target
------
Intended for early development workflow testing on EOS 750D / Rebel T6i.
Use a known-good firmware baseline and test conservatively.

Notes
-----
- The included GitHub Actions workflow validates repository structure and
  archives module sources, but does not perform a real Magic Lantern compile
  by itself.
- A real compile requires the full upstream ML source tree.
- If your chosen upstream ML tree does not export the symbol
  ``get_halfshutter_pressed()``, replace that call with the exact equivalent
  used by a currently working module in the same tree.
