750D Dev Sanity Module (sanity750)
=================================

Purpose
-------
A very conservative first Magic Lantern module intended for safe bring-up and
workflow validation on EOS 750D / Rebel T6i development setups.

This module intentionally stays in low-risk territory:

- Menu entries
- Persistent config values
- Console output

It avoids low-level camera internals and advanced hooks.

Features (v0.1)
---------------
- Run 750D sanity check
- Show last result
- Reset sanity counters
- Log to file toggle (reserved for future implementation)

Persistent config keys
----------------------
- ``sanity.run_count``
- ``sanity.last_status``
- ``sanity.log_to_file``

Build
-----
From repository root or module directory, use your standard ML module build
workflow for target camera firmware (e.g. 750D.110 in an ML tree).

Deploy
------
Copy resulting ``sanity750.mo`` to:

::

    ML/MODULES/

Enable in the Modules menu and restart camera to load.

Safety notes
------------
Magic Lantern development is inherently experimental. Keep a known-good card,
validate on stable firmware, and test incrementally.
