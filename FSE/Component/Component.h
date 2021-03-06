#pragma once

#include <rttr/type>

struct b2Manifold;
class b2Contact;
struct b2ContactImpulse;

namespace fse
{
	class FSEObject;
	/*!
	 * \brief Base class for object components;
	 */
	class Component
	{
	public:
		Component();
		virtual ~Component() = default;
		/*!
		 * \brief Call every frame to update the component
		 * \param deltaTime elapsed time in seconds
		 */
		virtual void update(float deltaTime) = 0;

		virtual void onAttach();
		virtual void onDetach();



		FSEObject* getAttachedObject() const;
		void attachToObject(FSEObject* object);

		bool isAttached() const;

		void detach();

		/*!
		* \brief Called on Contact begin
		* Refer to Box2D doc
		*
		* \param otherObject Ptr to other object
		* \param contact Ptr to b2Contact class
		*/
		virtual void BeginContact(FSEObject* otherObject, b2Contact* contact);
		/*!
		* \brief Called on Contact end
		* Refer to Box2D doc
		* \param otherObject Ptr to other object
		* \param contact Ptr to b2Contact class
		*/
		virtual void EndContact(FSEObject* otherObject, b2Contact* contact);
		/*!
		* \brief Called before solving collision
		* Refer to Box2D doc
		*
		* \param otherObject Ptr to other object
		* \param contact Ptr to b2Contact class
		* \param oldManifold Ptr to old contact manifold
		*/
		virtual void PreSolve(FSEObject* otherObject, b2Contact* contact, const b2Manifold* oldManifold);
		/*!
		* \brief Called after solving collision
		* Refer to Box2D doc
		*
		* \param otherObject Ptr to other object
		* \param contact Ptr to b2Contact class
		* \param impulse Ptr to contact impulse
		*/
		virtual void PostSolve(FSEObject* otherObject, b2Contact* contact, const b2ContactImpulse* impulse);

	protected:
		FSEObject* object_ = nullptr;

	private:
		RTTR_ENABLE()
		RTTR_REGISTRATION_FRIEND
	};
}
