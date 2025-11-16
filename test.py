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
from rembg import remove
from PIL import Image

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
        original_filename = f"logo_original_{timestamp}.png"
        with open(original_filename, 'wb') as f:
            f.write(img_data)
        print(f"✅ Original saved: {original_filename}")

        # Remove background to make transparent
        print(f"🔄 Removing background...")
        input_image = Image.open(BytesIO(img_data))
        output_image = remove(input_image)

        # Save transparent version
        transparent_filename = f"logo_transparent_{timestamp}.png"
        output_image.save(transparent_filename)
        print(f"✅ Transparent logo saved: {transparent_filename}")
        print(f"🔗 Direct URL: {image_url}")

        return transparent_filename

    except Exception as e:
        print(f"❌ Error: {e}")
        return None


if __name__ == "__main__":
    # Sleek abstract minimalist tech logo
    prompt = "Abstract minimalist logo: three ascending geometric bars transforming into flowing data streams, monochromatic midnight blue, clean angular shapes, negative space, perfect symmetry, ultra-sleek vector design, flat style, modern fintech aesthetic, no gradients, corporate tech branding"

    generate_logo(prompt)
