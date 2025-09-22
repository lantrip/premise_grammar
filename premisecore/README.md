# premisecore (Python)

Python bindings for the Rust premise-core library. Built with PyO3 + maturin.

Quickstart

- Create venv and install in develop mode:

```
python -m venv .venv
source .venv/bin/activate
pip install maturin
maturin develop
```

- Usage:

```python
import premisecore
p = premisecore.Parser()
print(p.parse_json("", False, False, False))
print(premisecore.schema("parse"))
```
