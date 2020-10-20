from flask import Flask, request

app = Flask(__name__)


@app.route("/")
def handler():
    return f"Hello, {request}"


if __name__ == "__main__":
    app.run(host="localhost", port=5000)
