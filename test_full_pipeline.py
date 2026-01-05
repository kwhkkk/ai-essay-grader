# test_full_pipeline.py
"""
端到端测试：OCR + 大模型批改
1. 识别 test.jpg 中的英文作文
2. 调用阿里云百炼批改
3. 输出结构化结果
"""
import os
import json
from ocr.ocr_engine import extract_text_from_image
from llm.grader import grade_essay


def main():
    # === 1. 检查测试图片是否存在 ===
    image_path = "test.jpg"
    if not os.path.exists(image_path):
        print(f"❌ 错误：测试图片未找到！请将作文图片保存为: {os.path.abspath(image_path)}")
        return

    print("🔍 步骤 1: 执行 OCR 识别...")
    print("-" * 50)

    # === 2. 执行 OCR ===
    ocr_text = extract_text_from_image(image_path)
    if ocr_text.startswith("OCR 识别失败") or ocr_text.startswith("错误："):
        print(f"❌ OCR 失败: {ocr_text}")
        return

    print("✅ OCR 识别成功！识别文本：")
    print(ocr_text)
    print("\n" + "=" * 50)

    # === 3. 执行大模型批改 ===
    print("🧠 步骤 2: 调用大模型批改...")
    print("-" * 50)

    if not ocr_text.strip():
        print("❌ 作文内容为空，无法批改")
        return

    grade_result = grade_essay(ocr_text)

    # === 4. 输出批改结果 ===
    print("✅ 批改完成！结果如下：")
    print(json.dumps(grade_result, indent=2, ensure_ascii=False))

    # === 5. 计算总分（可选）===
    total_score = (
            grade_result.get("content_score", 0) +
            grade_result.get("grammar_score", 0) +
            grade_result.get("vocabulary_score", 0) +
            grade_result.get("coherence_score", 0)
    )
    print(f"\n📊 总分: {total_score}/40")


if __name__ == "__main__":
    main()