#pragma once
#include <sstream>

template <typename Class>
class AbstractMember
{
public:
	virtual ~AbstractMember() {}
	virtual std::string toString(const Class& object) = 0;
	virtual void fromStringStream(Class& object, std::stringstream& ss) = 0;
};

template <typename Class, typename T>
class Member : public AbstractMember<Class>
{
public:
	Member(T Class::* pointer) : m_memberPointer(pointer) {}
	std::string toString(const Class& object)
	{
		return std::to_string(object.*m_memberPointer);
	}
	void fromStringStream(Class& object, std::stringstream& ss)
	{
		ss >> object.*m_memberPointer;
	}
private:
	T Class::* m_memberPointer;
};

//specialization for std::string
template <typename Class>
class Member<Class, std::string> : public AbstractMember<Class>
{
public:
	Member(std::string Class::* pointer) : m_memberPointer(pointer) {}
	std::string toString(const Class& object)
	{
		return object.*m_memberPointer;
	}
	void fromStringStream(Class& object, std::stringstream& ss)
	{
		ss >> object.*m_memberPointer;
	}
private:
	std::string Class::* m_memberPointer;
};

//specialization for sf::IntRect
template <typename Class>
class Member<Class, sf::IntRect> : public AbstractMember<Class>
{
public:
	Member(sf::IntRect Class::* pointer) : m_memberPointer(pointer) {}
	std::string toString(const Class& object)
	{
		std::stringstream ss;
		ss << object.*m_memberPointer.left;
		ss << object.*m_memberPointer.top;
		ss << object.*m_memberPointer.width;
		ss << object.*m_memberPointer.height;
		std::string result;
		ss >> result;
		return result;
	}
	void fromStringStream(Class& object, std::stringstream& ss)
	{
		ss >> object.*m_memberPointer.left;
		ss >> object.*m_memberPointer.top;
		ss >> object.*m_memberPointer.width;
		ss >> object.*m_memberPointer.height;
	}
private:
	sf::IntRect Class::* m_memberPointer;
};

template <typename Class>
class ClassMetaInfo
{
public:
	template <typename T>
	static void registerMember(const std::string& name, T Class::* pointer)
	{
		m_members.emplace(name, std::make_unique<Member<Class, T>>(pointer));
	}

	static std::string serialize(const Class& object)
	{
		std::string result;
		for (const auto& pair : m_members)
		{
			std::stringstream ss;
			ss << pair.first << ' ';
			ss << pair->second->toString(object) << std::endl;
		}
		ss >> result;
		return result;
	}

	static void deserialize(const Class& object, std::stringstream& ss)
	{
		for (const auto& pair : m_members)
		{
			ss >> pair.first;
			ss >> pair.second->fromStringStream(ss);
		}
	}

private:
	static std::unordered_map<std::string, std::unique_ptr<AbstractMember<Class>>> m_members;
};

template<typename Class>
std::unordered_map<std::string, std::unique_ptr<AbstractMember<Class>>> ClassMetaInfo<Class>::m_members;