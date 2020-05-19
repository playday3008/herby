#pragma once
#include "recv.hpp"
#include "sdk/interfaces/IClientEntity.hpp"

typedef IClientNetworkable* (*CreateClientClassFn)(int iEntNum, int iSerialNum);
typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	static IClientNetworkable* NewClass(ClientClass* head, const char* name, int index, int serial)
	{
		CreateClientClassFn fn = nullptr;
		for (auto cc = head; cc; cc = cc->m_pNext) {
			if (!strcmp(cc->m_pNetworkName, name)) {
				fn = cc->m_pCreateFn;
				break;
			}
		}
		if (fn) {
			return fn(index, serial);
		}
		else return nullptr;
	}
	static IClientNetworkable* NewEvent(ClientClass* head, const char* name)
	{
		CreateEventFn fn = nullptr;
		for (auto cc = head; cc; cc = cc->m_pNext) {
			if (!strcmp(cc->m_pNetworkName, name)) {
				fn = cc->m_pCreateEventFn;
				break;
			}
		}
		if (fn) {
			return fn();
		}
		else return nullptr;
	}

	CreateClientClassFn		m_pCreateFn;
	CreateEventFn			m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int						m_ClassID;
};