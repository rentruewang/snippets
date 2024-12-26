# Copyright (c) RenChu Wang - All Rights Reserved


class TestClass:
    def __init__(self) -> None:
        self.x = 1
        print(self.x)

    def __getattr__(self, attr: str) -> None:
        print(attr)
        return 10


if __name__ == "__main__":
    TestClass().y
