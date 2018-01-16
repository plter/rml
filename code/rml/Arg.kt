package rml

class Arg(value: String?, refName: String?, parent: Scope?) : Scope(parent) {

    private val _value = value

    private val _refName = refName

    fun getValue(): Any? {
        return _value ?: if (_refName != null) {
            val v = getVar(_refName)
            if (v != null) {
                v.value
            } else {
                getFunc(_refName)
            }
        } else null
    }

}