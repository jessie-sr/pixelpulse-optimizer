from pathlib import Path
import hashlib
import sys


proj_dir_path = Path(__file__).parent.parent

starter_file_hashes = {
    "Makefile": "37be02d8138528a7732392f545ced469",
    "src/compute.h": "2517f5b78999da553924cc3bdc88d661",
    "src/coordinator.h": "66caa337c52639a200cd70bf881abb6b",
    "src/io.h": "cd438edde87210d259d7425731be6e37",
    "src/io.o": "6ec54fad1205fd112ea755eadcf74238",
    "tools/check_output.sh": "90abd43257eb688aa86abecae04c68db",
    "tools/create_tests.py": "fbd72ce779c69a7c131889c5bfa1e398",
    "tools/framework.py": "90eb1bb3115e7254dc44b6a3f29f6fc9",
    "tools/results_to_gif.py": "990fba3042d1ba07718c0e240f31f14e",
    "tools/run_test.sh": "fd44999a528c848997de2cb07b12b6e9",
    "tools/staff_tests.py": "3055796b45630254ac8c8422ac5d9b47",
}

def check_hash(rel_path_str):
    if rel_path_str not in starter_file_hashes:
        return (True, f"Starter does not have hash for {rel_path_str}")
    path = proj_dir_path / rel_path_str
    with path.open("rb") as f:
        contents = f.read()
    contents = contents.replace(b"\r\n", b"\n")
    hashed_val = hashlib.md5(contents).hexdigest()
    if hashed_val != starter_file_hashes[rel_path_str]:
        return (False, f"{rel_path_str} was changed from starter")
    return (True, f"{rel_path_str} matches starter file")

passed_all = True
for rel_path_str in starter_file_hashes.keys():
    passed, reason = check_hash(rel_path_str)
    if not passed:
        passed_all = False
        print(f"Error: {reason}", file=sys.stderr)
if not passed_all:
    sys.exit(1)
