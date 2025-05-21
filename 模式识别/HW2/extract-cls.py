import torch
import timm
import numpy as np
from PIL import Image
from torchvision import transforms
import os
import random

# 设置全局随机种子
seed = 221300066
random.seed(seed)
torch.manual_seed(seed)
np.random.seed(seed)

# 加载模型并设置为评估模式
model = timm.create_model('vit_tiny_patch16_224.augreg_in21k', pretrained=True)
model.eval()
device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
model.to(device)

# 获取模型对应的预处理方法
data_config = timm.data.resolve_model_data_config(model)
transform = timm.data.create_transform(**data_config, is_training=False)

# 数据集路径
dataset_path = 'CUB_200_2011/images/'
class_folders = sorted([f for f in os.listdir(dataset_path) if os.path.isdir(os.path.join(dataset_path, f))])

features = []

for class_idx, folder in enumerate(class_folders):
    # 设置每个类别的独立随机种子
    class_seed = seed + class_idx
    random.seed(class_seed)

    class_path = os.path.join(dataset_path, folder)
    images = sorted([f for f in os.listdir(class_path) if f.lower().endswith(('.jpg', '.jpeg', '.png'))])

    # 随机选择一张图像
    selected_img = random.choice(images)
    img_path = os.path.join(class_path, selected_img)

    # 加载并预处理图像
    img = Image.open(img_path).convert('RGB')
    img_tensor = transform(img).unsqueeze(0).to(device)

    # 前向传播获取特征
    with torch.no_grad():
        features_out = model.forward_features(img_tensor)
        cls_token = features_out[0, 0].cpu().numpy()  # 提取CLS token

    features.append(cls_token)

# 保存特征
features_array = np.array(features)
np.save('cls_features.npy', features_array)
print(f'Successfully extracted {len(features_array)} CLS tokens, dimension: {features_array.shape[1]}')