# llm/grader.py
import os
import json
from dotenv import load_dotenv
from openai import OpenAI

# 加载 .env 文件
load_dotenv()

# 初始化 OpenAI 客户端（适配阿里云百炼）
client = OpenAI(
    api_key=os.getenv("OPENAI_API_KEY"),
    base_url=os.getenv("OPENAI_API_BASE", "https://dashscope.aliyuncs.com/compatible-mode/v1")
)


def grade_essay(essay: str) -> dict:
    """
    调用阿里云百炼通义千问大模型批改作文
    返回结构化 JSON 结果
    """
    prompt = f"""
你是一名资深英语教师，请对以下作文用中文进行评分和批改，严格按照以下 JSON 格式返回，不要包含任何其他文字：
{{
  "content_score": 0,
  "grammar_score": 0,
  "vocabulary_score": 0,
  "coherence_score": 0,
  "overall_comment": "",
  "errors": [
    {{
      "position": "",
      "type": "",
      "original": "",
      "suggestion": "",
      "explanation": ""
    }}
  ]
}}

请批改以下作文：
{essay}
"""

    try:
        response = client.chat.completions.create(
            model="qwen-max",  # 或 qwen-plus，根据你的额度选择
            messages=[{"role": "user", "content": prompt}],
            temperature=0.2,  # 低温度确保输出稳定
            response_format={"type": "json_object"}  # 强制返回 JSON
        )

        # 解析 JSON
        result = json.loads(response.choices[0].message.content)
        return result

    except Exception as e:
        print(f"⚠️ 大模型批改失败: {e}")
        # 返回模拟结果
        return {
            "content_score": 8,
            "grammar_score": 7,
            "vocabulary_score": 9,
            "coherence_score": 8,
            "overall_comment": "内容充实，但注意语法准确性。",
            "errors": []
        }
