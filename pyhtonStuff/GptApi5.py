import json
import requests
from flask import Flask, jsonify, request
from llama_cpp import Llama

app = Flask(__name__)
# load the large language model file
LLM = Llama(model_path="./llama-2-7b-chat.Q8_0.gguf")


@app.route('/askgpt', methods=['POST'])
def query_gpt():
    data = request.json
    question = data.get("question")
    # Call ChatGPT API with the question
    response = call_chatgpt_api(question)

    if response == "error":
        # Call LLama2 API with the question if ChatGpt API fails
        response = call_llama_gpt_api(question)
    
    return jsonify({"response": response}), 200


def call_chatgpt_api(question):
    # Call ChatGPT API with the question
    url = "https://api.openai.com/v1/completions"

    payload = json.dumps({
        "model": "gpt-3.5-turbo-instruct",
        "prompt": f"{question}" ,
        "max_tokens": 1024
    })
    headers = {
        'Content-Type': 'application/json',
    }
    # key removed

    response = requests.request("POST", url, headers=headers, data=payload)
    data = json.loads(response.text)
    
    error_message = data['error']['message']

    if error_message:
        return "error"
    
    answer = data.get("text") 
    return answer


def call_llama_gpt_api(question):
    # Call LLama2 API with the question

    # create a text prompt
    prompt = question

    # generate a response (takes several seconds)
    Llama_says = LLM(prompt, max_tokens=1024, temperature=0)

    # return the response
    answer = Llama_says["choices"][0]["text"]
    return answer


if __name__ == '__main__':
    app.run(debug=True, port = 5001)

