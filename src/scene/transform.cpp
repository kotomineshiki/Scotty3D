
#include "transform.h"

Mat4 Transform::local_to_parent() const {
	return Mat4::translate(translation) * rotation.to_mat() * Mat4::scale(scale);
}

Mat4 Transform::parent_to_local() const {
	return Mat4::scale(1.0f / scale) * rotation.inverse().to_mat() * Mat4::translate(-translation);
}

Mat4 Transform::local_to_world() const {
	//A1T1: local_to_world
	//don't use Mat4::inverse() in your code.
	if (std::shared_ptr< Transform > parent_ = parent.lock()) {
		//case where transform has a parent
		//...
		Mat4 result1 = parent_->local_to_world();

		Mat4 result2= local_to_parent();
		return result1*result2;
	}
	else {
		//case where transform doesn't have a parent,should be the local to parent
		//...
		return local_to_parent();
	}
	//return Mat4::I; //<-- wrong, but here so code will compile
}

Mat4 Transform::world_to_local() const {
	//A1T1: world_to_local
	//don't use Mat4::inverse() in your code.
	if (std::shared_ptr< Transform > parent_ = parent.lock()) {
		//case where transform has a parent
		//...
		Mat4 result1 = parent_->world_to_local();

		Mat4 result2 = parent_to_local();
		return  result2*result1;
	}
	else {
		//case where transform doesn't have a parent,should be the local to parent
		//...
		return parent_to_local();
	}
	//return local_to_world().inverse(); //<-- wrong, but here so code will compile
}

bool operator!=(const Transform& a, const Transform& b) {
	return a.parent.lock() != b.parent.lock() || a.translation != b.translation ||
	       a.rotation != b.rotation || a.scale != b.scale;
}
