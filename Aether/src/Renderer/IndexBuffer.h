#pragma once

namespace Aether {
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;
		
		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) = 0;
		virtual void Bind() const = 0;

		virtual uint32_t GetCount() const = 0;
		
		virtual uint32_t GetSize() const = 0;

		static Ref<IndexBuffer> Create(void* data, uint32_t size);
	};
}