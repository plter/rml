package rml

abstract class XMLReader(source: String?, fileId: String = "untitled") {

    private val _source = source
    private var _lineNum = 0

    private val _fileId = fileId
    val fileId: String get() = _fileId

    val currentLineNum: Int get() = _lineNum

    fun read() {
        if (_source != null) {
            var index = 0
            val sourceLength = _source.length
            _lineNum = 1
            topLoop@ while (index < sourceLength) {
                var c = _source[index]
                when (c) {
                    '<' -> {
                        index += 1

                        c = _source[index]
                        when (c) {
                            '/' -> {
                                val endTagSB = StringBuilder()
                                index += 1
                                while (index < sourceLength) {
                                    c = _source[index]

                                    if (c != '>') {
                                        endTagSB.append(c)
                                    } else {
                                        break
                                    }
                                    index++
                                }
                                elementEnd(endTagSB.toString())
                            }
                            '!' -> {
                                if (_source[index + 1] == '-' && _source[index + 2] == '-') {
                                    index += 3
                                    val contentSB = StringBuilder()
                                    while (index < sourceLength) {
                                        c = _source[index]
                                        if (c == '-' && _source[index + 1] == '-' && _source[index + 2] == '>') {
                                            break
                                        } else {
                                            contentSB.append(c)
                                        }
                                        index++
                                    }
                                    commentContent(contentSB.toString())
                                }
                            }
                            ' ', '\r', '\n' -> {
                                println("Syntax error at line $_lineNum")
                                break@topLoop
                            }
                            else -> {
                                var sb = StringBuilder()
                                val attributes = HashMap<String, String>()
                                var tag: String? = null
                                findAttributesLoop@ while (index < sourceLength) {
                                    c = _source[index]

                                    when (c) {
                                        ' ' -> {
                                            if (tag == null) {
                                                tag = sb.toString()
                                            }
                                            sb = StringBuilder()
                                        }
                                        '=' -> {
                                            val name = sb.toString()
                                            val valueSB = StringBuilder()
                                            index += 1
                                            var foundStart = false
                                            while (index < sourceLength) {
                                                c = _source[index]
                                                if (c != '"') {
                                                    if (foundStart) {
                                                        if (c != '\\') {
                                                            valueSB.append(c)
                                                        } else {
                                                            when (_source[index + 1]) {
                                                                'n' -> {
                                                                    valueSB.append('\n')
                                                                    index++
                                                                }
                                                                'r' -> {
                                                                    valueSB.append('\r')
                                                                    index++
                                                                }//TODO support more words
                                                                else -> {
                                                                    valueSB.append(c)
                                                                }
                                                            }
                                                        }
                                                    }
                                                } else {
                                                    if (!foundStart) {
                                                        foundStart = true
                                                    } else {
                                                        val value = valueSB.toString()
                                                        attributes[name] = value
                                                        break
                                                    }
                                                }

                                                index++
                                            }
                                        }
                                        '/' -> {
                                            if (tag == null) {
                                                tag = sb.toString()
                                            }
                                            if (_source[index + 1] == '>') {
                                                elementStart(tag, attributes)
                                                elementEnd(tag)
                                                break@findAttributesLoop
                                            } else {
                                                println("Syntax error at line $_lineNum")
                                                break@topLoop
                                            }
                                        }
                                        '>' -> {
                                            if (tag == null) {
                                                tag = sb.toString()
                                            }
                                            elementStart(tag, attributes)
                                            break@findAttributesLoop
                                        }
                                        else -> {
                                            sb.append(c)
                                        }
                                    }

                                    index++
                                }
                            }
                        }
                    }
                    '\n' -> ++_lineNum
                }

                index++
            }
        }
    }

    protected abstract fun elementStart(tagName: String, attributes: Map<String, String>)
    protected abstract fun elementEnd(tagName: String)
    protected abstract fun commentContent(content: String)


}