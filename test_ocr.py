# test_ocr.py
"""
OCR 功能测试脚本
- 测试 Tesseract OCR 引擎
- 验证英文作文识别效果
"""
import os
from ocr.ocr_engine import extract_text_from_image


def main():
    # === 配置测试图片路径 ===
    # 方式1: 使用项目根目录下的 test.jpg
    image_path = "test.jpg"

    # 方式2: 使用绝对路径（推荐，避免中文路径问题）
    # image_path = r"D:\projects\ai-essay-grader\test.jpg"

    # === 检查图片是否存在 ===
    if not os.path.exists(image_path):
        print(f"❌ 错误：测试图片未找到！")
        print(f"请将英文作文图片保存为: {os.path.abspath(image_path)}")
        print("\n推荐操作：")
        print("1. 下载测试图: https://github.com/PaddlePaddle/PaddleOCR/raw/release/2.6/doc/imgs_en/img_12.jpg")
        print("2. 重命名为 test.jpg")
        print("3. 放在项目根目录")
        return

    print(f"🔍 正在识别图片: {os.path.abspath(image_path)}")
    print("-" * 50)

    # === 执行 OCR ===
    result = extract_text_from_image(image_path)

    # === 输出结果 ===
    if result.startswith("OCR 识别失败") or result.startswith("错误："):
        print(f"❌ {result}")
    else:
        print("✅ OCR 识别成功！")
        print("\n=== 识别结果 ===")
        print(result)
        print("\n" + "=" * 50)
        print("💡 提示：")
        print("- 如果手写体识别不准确，请确保图片清晰")
        print("- 印刷体英文识别准确率 >95%")
        print("- 后续将接入大模型进行作文批改")

if __name__ == "__main__":
    main()