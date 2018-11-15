#include "stdafx.h"
#include "RectangleCollider.h"
#include "DirectXRenderer.h"

using namespace DirectX;

RectangleCollider::RectangleCollider():
	m_pGameObject(nullptr),
	m_pRect(nullptr)
{
	
}


RectangleCollider::~RectangleCollider()
{
	Release();
}

//void RectangleCollider::Create(GameObject* object, Vertex(&vertexArray) ) {
//	
//	Create(object);
//	float min_x = 0;
//	float max_x = 0;
//
//	float min_y = 0;
//	float max_y = 0;
//
//	for (size_t i = 0; i < sizeof(vertexArray)/sizeof(Vertex); i++)
//	{
//
//	}
//}

void RectangleCollider::Create(GameObject* object, ImageVertex(&vertexArray)[4]) {

	Create(object);

	float min_x = 0;
	float max_x = 0;

	float min_y = 0;
	float max_y = 0;

	int size = sizeof(vertexArray) / sizeof(ImageVertex);

	for (size_t i = 0; i < sizeof(vertexArray) / sizeof(ImageVertex); i++)
	{
		// x���W�̍ő�l���X�V����
		if (vertexArray[i].m_vertPos.x > max_x) {
			max_x = vertexArray[i].m_vertPos.x;
		}

		// x���W�̍ŏ��l���X�V����
		if (vertexArray[i].m_vertPos.x < min_x) {
			min_x = vertexArray[i].m_vertPos.x;
		}

		// y���W�̍ő�l���X�V����
		if (vertexArray[i].m_vertPos.y > max_y) {
			max_y = vertexArray[i].m_vertPos.y;
		}

		// y���W�̍ŏ��l���X�V����
		if (vertexArray[i].m_vertPos.y < min_y) {
			min_y = vertexArray[i].m_vertPos.y;
		}
	}
	// ���ӂ̍��W��ݒ�
	m_pRect->left = min_x;
	// �E�ӂ̍��W��ݒ�
	m_pRect->right = max_x;

	// ��ӂ̍��W��ݒ�
	m_pRect->top = max_y;
	// ���ӂ̍��W��ݒ�
	m_pRect->bottom = min_y;

	m_pRect->CalcScale();
}

void RectangleCollider::Create(GameObject* object) {
	m_pGameObject = object;
	m_pRect = new RectangleVertex();
	DirectXRenderer::instance->AddCollider(this);
}

void RectangleCollider::Release() {
	DirectXRenderer::instance->RemoveCollider(this);
	delete(m_pRect);
}

bool RectangleCollider::CheckCollider(RectangleCollider * collider)
{

	RectangleVertex checkRect = collider->GetRect();

	RectangleVertex myRect = GetRect();

	//���ɏd�Ȃ��Ă����ꍇ
	if (myRect.left <= checkRect.right && myRect.right >= checkRect.left)
	{
		//�c�ɏd�Ȃ��Ă����ꍇ
		if (myRect.top >= checkRect.bottom && myRect.bottom <= checkRect.top)
		{
			return true;
		}

	}
	return false;
}

RectangleVertex RectangleCollider::GetRect()
{
	RectangleVertex rect = RectangleVertex();

	// ���_���W�����[���h���W�ɕϊ�����
	// ��
	rect.left = (m_pGameObject->m_transform->m_pos.x) + (m_pRect->left);
	// ��
	rect.top = (m_pGameObject->m_transform->m_pos.y) + (m_pRect->top);
	// �E
	rect.right = (m_pGameObject->m_transform->m_pos.x) + (m_pRect->right);
	// ��
	rect.bottom = (m_pGameObject->m_transform->m_pos.y) + (m_pRect->bottom);

	return rect;
}