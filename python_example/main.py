import asyncio


async def aprint(string, seconds):
    await asyncio.sleep(seconds)
    print(string)


async def main():
    async def print_something():
        await aprint("b", 3)
        await aprint("c", 1)

    async def print_other():
        await aprint("a", 2)

    await asyncio.gather(print_something(), print_other())


if __name__ == "__main__":
    asyncio.run(main())
