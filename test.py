"""
Logo generator with automatic background removal
Usage: pip install openai requests rembg pillow
       python test.py
"""
import os
from openai import OpenAI
import requests
from datetime import datetime
from io import BytesIO

client = OpenAI(api_key=os.getenv("OPENAI_API_KEY"))

def generate_logo(prompt: str):
    """Generate a logo from a text prompt."""

    # Enhance prompt for white background (easier to remove)
    enhanced_prompt = f"{prompt}, on a pure white background, centered, isolated object, clean edges, vector art style"

    print(f"🎨 Generating logo...")
    print(f"Prompt: {prompt}\n")

    try:
        # Generate image
        response = client.images.generate(
            model="dall-e-3",
            prompt=enhanced_prompt,
            size="1024x1024",
            quality="standard",
            n=1,
        )

        image_url = response.data[0].url
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")

        # Download image
        print(f"📥 Downloading image...")
        img_data = requests.get(image_url).content

        # Save original
        filename = f"logo_{timestamp}.png"
        with open(filename, 'wb') as f:
            f.write(img_data)
        print(f"✅ Logo saved: {filename}")
        print(f"🔗 Direct URL: {image_url}")

        return filename

    except Exception as e:
        print(f"❌ Error: {e}")
        return None


if __name__ == "__main__":
    prompt = "Abstract logo: AI brain circuit pattern merging with stock market candlesticks, neon blue and purple gradient, geometric shapes, minimal clean design, tech startup aesthetic"

    generate_logo(prompt)
