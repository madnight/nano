# Repository Guidelines (Milli)

## Project Structure & Module Organization
- `src/`: core Milli editor sources (C) plus headers like `definitions.h` and `prototypes.h`.
- `lib/`: gnulib support pulled in by autotools; avoid editing generated files.
- `syntax/`: syntax definitions installed when color support is enabled; keep new syntaxes small and documented for Milli users.
- `doc/`: manuals and examples (see `doc/sample.nanorc`), plus release notes and change logs.
- `po/` and `m4/`: localization and autotools macro glue; touch only if you know the tooling.
- Top-level helpers: `autogen.sh` (bootstrap), `configure.ac`/`Makefile.am` (build system), `nano-regress` (option-matrix build check for Milli builds).

## Build, Test, and Development Commands
- First-time from git: `./autogen.sh && ./configure --enable-debug` (generates `configure`, enables debug symbols).
- Standard build: `make` (produces `src/milli`, the Milli binary; rerun after code changes).
- Install locally: `make install` (use `--prefix` with `./configure` to change destination).
- Clean artifacts: `make clean` (or `make distclean` after reconfiguring).
- Stress configure options: `./nano-regress` (iterates common `./configure` flag combinations; noisy but useful before releasing Milli).

## Coding Style & Naming Conventions
- C code with tab width 4, aim to keep lines ≤80 characters (per `README.hacking`); follow existing brace placement and spacing.
- Prefer descriptive, lowercase_with_underscores identifiers; mirror surrounding naming for new functions and globals.
- Keep platform-specific code behind feature macros already used in the tree (e.g., `#ifdef ENABLE_UTF8`).
- Update or add comments only when clarifying non-obvious behavior; avoid restating the code.

## Testing Guidelines
- There is no dedicated automated test suite; rely on `./nano-regress` plus manual Milli editor exercises for features you touch.
- After building, sanity check with `./src/milli --version` and a short Milli edit session (open, search/replace, save).
- When changing syntax files, confirm loading via `--rcfile` pointing to the modified sample file.

## Commit & Pull Request Guidelines
- Use small, focused commits with a clear, imperative subject (examples: `tweaks: adjust scrollbar jump`, `mouse: allow pre-answer click`).
- Include a Signed-off-by line (`git commit -as`) and add a short rationale in the message body when the change is non-trivial.
- Branch from `master`, keep changes rebased, and reference related bug IDs or mailing list threads when applicable.
- For PRs or patches, describe user-visible impact, mention configuration flags touched, and include any manual test notes or screenshots relevant to UI behavior.
