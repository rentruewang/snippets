# Copyright (c) RenChu Wang - All Rights Reserved

import asyncio


async def wait(time: int) -> None:
    await asyncio.sleep(time)
    print(f"After waiting: {time}s")


async def aprint(string, seconds):
    await asyncio.sleep(seconds)
    print(string)


async def main():
    tasks = []
    tasks.append(asyncio.create_task(wait(5)))
    tasks.append(asyncio.create_task(wait(3)))

    for task in tasks:
        await task

    async def print_something():
        await aprint("b", 3)
        await aprint("c", 1)

    async def print_other():
        await aprint("a", 2)

    await asyncio.gather(print_something(), print_other())


if __name__ == "__main__":
    asyncio.run(main())
