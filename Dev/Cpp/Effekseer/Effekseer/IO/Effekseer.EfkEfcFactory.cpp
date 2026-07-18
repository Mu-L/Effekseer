#include "Effekseer.EfkEfcFactory.h"
#include "../Utils/Effekseer.BinaryReader.h"

namespace Effekseer
{

EfkEfcFile::EfkEfcFile(const void* data, int32_t size)
	: data_(data)
	, size_(size)
{
	if (data == nullptr || size < 0)
		return;
	BinaryReader<true> binaryReader(reinterpret_cast<const uint8_t*>(data_), static_cast<size_t>(size_));

	// EFKP
	int head = 0;
	if (!binaryReader.Read(head) || memcmp(&head, "EFKE", 4) != 0)
		return;

	if (!binaryReader.Read(version_))
		return;

	isValid_ = true;
}

EfkEfcFile::Chunk EfkEfcFile::ReadChunk(const char* forcc) const
{
	if (!IsValid())
		return {};

	BinaryReader<true> binaryReader(reinterpret_cast<const uint8_t*>(data_), static_cast<size_t>(size_));

	// Skip forcc and version
	binaryReader.AddOffset(8);

	// read chunk
	while (binaryReader.GetOffset() < size_)
	{
		int chunkForcc = 0;
		if (!binaryReader.Read(chunkForcc))
			return {};
		int chunkSize = 0;
		if (!binaryReader.Read(chunkSize) || chunkSize < 0 || !binaryReader.CanRead(static_cast<size_t>(chunkSize)))
			return {};

		if (memcmp(&chunkForcc, forcc, 4) == 0)
		{
			Chunk chunk;
			chunk.data = reinterpret_cast<const uint8_t*>(data_) + binaryReader.GetOffset();
			chunk.size = chunkSize;
			return chunk;
		}

		if (!binaryReader.Skip(static_cast<size_t>(chunkSize)))
			return {};
	}

	return {};
}

EfkEfcFile::Chunk EfkEfcFile::ReadInfo() const
{
	return ReadChunk("INFO");
}

EfkEfcFile::Chunk EfkEfcFile::ReadEditerData() const
{
	return ReadChunk("EDIT");
}

EfkEfcFile::Chunk EfkEfcFile::ReadRuntimeData() const
{
	return ReadChunk("BIN_");
}

bool EfkEfcFactory::OnLoading(Effect* effect, const void* data, int32_t size, float magnification, const char16_t* materialPath)
{
	EfkEfcFile file(data, size);

	if (!file.IsValid())
	{
		return false;
	}

	auto chunk = file.ReadRuntimeData();
	if (chunk.data == nullptr)
	{
		return false;
	}

	return LoadBody(effect, chunk.data, chunk.size, magnification, materialPath);
}

bool EfkEfcFactory::OnCheckIsBinarySupported(const void* data, int32_t size)
{
	EfkEfcFile file(data, size);

	return file.IsValid();
}

bool EfkEfcProperty::Load(const void* data, int32_t size)
{
	EfkEfcFile file(data, size);

	if (!file.IsValid())
	{
		return false;
	}

	auto chunk = file.ReadRuntimeData();
	if (chunk.data == nullptr)
	{
		return false;
	}

	BinaryReader<true> binaryReader(static_cast<const uint8_t*>(chunk.data), static_cast<size_t>(chunk.size));

	int32_t infoVersion = 0;

	constexpr int32_t elementCountMax = 1024;
	auto loadStr = [&binaryReader, &infoVersion, elementCountMax](std::vector<std::u16string>& dst) -> bool
	{
		int32_t dataCount = 0;
		if (!binaryReader.Read(dataCount))
			return false;

		// compatibility
		if (dataCount >= 1500)
		{
			infoVersion = dataCount;
			if (!binaryReader.Read(dataCount))
				return false;
		}
		if (dataCount < 0 || dataCount > elementCountMax)
			return false;
		dst.resize(dataCount);

		std::vector<char16_t> strBuf;

		for (int i = 0; i < dataCount; i++)
		{
			int length = 0;
			if (!binaryReader.Read(length) || length <= 0 || length > 32768 ||
				!binaryReader.CanReadElements(length, sizeof(char16_t)))
				return false;
			strBuf.resize(static_cast<size_t>(length));
			if (!binaryReader.Read(strBuf.data(), length) || strBuf.back() != u'\0')
				return false;
			dst.at(i).assign(strBuf.data(), static_cast<size_t>(length - 1));
		}
		return true;
	};

	if (!loadStr(colorImages_) || !loadStr(normalImages_) || !loadStr(distortionImages_) ||
		!loadStr(models_) || !loadStr(sounds_))
		return false;

	if (infoVersion >= 1500)
	{
		if (!loadStr(materials_))
			return false;
	}

	return binaryReader.GetStatus() != BinaryReaderStatus::Failed;
}

const std::vector<std::u16string>& EfkEfcProperty::GetColorImages() const
{
	return colorImages_;
}
const std::vector<std::u16string>& EfkEfcProperty::GetNormalImages() const
{
	return normalImages_;
}
const std::vector<std::u16string>& EfkEfcProperty::GetDistortionImages() const
{
	return distortionImages_;
}
const std::vector<std::u16string>& EfkEfcProperty::GetSounds() const
{
	return sounds_;
}
const std::vector<std::u16string>& EfkEfcProperty::GetModels() const
{
	return models_;
}
const std::vector<std::u16string>& EfkEfcProperty::GetMaterials() const
{
	return materials_;
}

} // namespace Effekseer
