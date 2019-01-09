#pragma once
#include <sstream>
#include <memory>
#include <unordered_map>
#include "SFML/Graphics/Rect.hpp"
#include "Vector2D.h"

template <typename Class>
class AbstractMember
{
public:
	virtual ~AbstractMember() {}
	virtual std::string toString(const Class& object) const = 0;
	virtual void fromStringStream(Class& object, std::stringstream& ss) const = 0;
};

template <typename Class, typename T>
class Member : public AbstractMember<Class>
{
public:
	Member(T Class::* pointer) : m_memberPointer(pointer) {}
	std::string toString(const Class& object) const
	{
		return std::to_string(object.*m_memberPointer);
	}
	void fromStringStream(Class& object, std::stringstream& ss) const
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
	std::string toString(const Class& object) const
	{
		return object.*m_memberPointer;
	}
	void fromStringStream(Class& object, std::stringstream& ss) const
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
	std::string toString(const Class& object) const
	{
		std::stringstream ss;
		ss << (object.*m_memberPointer).left << ' ';
		ss << (object.*m_memberPointer).top << ' ';
		ss << (object.*m_memberPointer).width << ' ';
		ss << (object.*m_memberPointer).height;
		std::string result;
		ss >> result;
		return result;
	}
	void fromStringStream(Class& object, std::stringstream& ss) const
	{
		ss >> (object.*m_memberPointer).left;
		ss >> (object.*m_memberPointer).top;
		ss >> (object.*m_memberPointer).width;
		ss >> (object.*m_memberPointer).height;
	}
private:
	sf::IntRect Class::* m_memberPointer;
};

//specialization for Vector2f
template <typename Class>
class Member<Class, Vector2f> : public AbstractMember<Class>
{
public:
	Member(Vector2f Class::* pointer) : m_memberPointer(pointer) {}
	std::string toString(const Class& object) const
	{
		std::stringstream ss;
		ss << (object.*m_memberPointer).x << ' ';
		ss << (object.*m_memberPointer).y;
		std::string result;
		ss >> result;
		return result;
	}
	void fromStringStream(Class& object, std::stringstream& ss) const
	{
		ss >> (object.*m_memberPointer).x;
		ss >> (object.*m_memberPointer).y;
	}
private:
	Vector2f Class::* m_memberPointer;
};

//Main meta info class
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
		std::stringstream ss;
		for (const auto& pair : m_members)
		{
			ss << pair.first << ' ';
			ss << pair->second->toString(object) << std::endl;
		}
		ss >> result;
		return result;
	}

	static void deserialize(Class& object, std::stringstream& ss)
	{
		for (auto& pair : m_members)
		{
			std::string memberName;
			ss >> memberName;
			m_members[memberName]->fromStringStream(object, ss);
		}
	}

private:
	static std::unordered_map<std::string, std::unique_ptr<AbstractMember<Class>>> m_members;
};

template<typename Class>
std::unordered_map<std::string, std::unique_ptr<AbstractMember<Class>>> ClassMetaInfo<Class>::m_members;