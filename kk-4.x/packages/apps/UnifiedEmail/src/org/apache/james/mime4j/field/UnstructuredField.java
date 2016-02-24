/****************************************************************
 * Licensed to the Apache Software Foundation (ASF) under one   *
 * or more contributor license agreements.  See the NOTICE file *
 * distributed with this work for additional information        *
 * regarding copyright ownership.  The ASF licenses this file   *
 * to you under the Apache License, Version 2.0 (the            *
 * "License"); you may not use this file except in compliance   *
 * with the License.  You may obtain a copy of the License at   *
 *                                                              *
 *   http://www.apache.org/licenses/LICENSE-2.0                 *
 *                                                              *
 * Unless required by applicable law or agreed to in writing,   *
 * software distributed under the License is distributed on an  *
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY       *
 * KIND, either express or implied.  See the License for the    *
 * specific language governing permissions and limitations      *
 * under the License.                                           *
 ****************************************************************/

package org.apache.james.mime4j.field;

import org.apache.james.mime4j.decoder.DecoderUtil;


/**
 * Simple unstructured field such as <code>Subject</code>.
 *
 * 
 * @version $Id: //DTV/MP_BR/DTV_X_IDTV0801_002298_3_001/android/kk-4.x/packages/apps/UnifiedEmail/src/org/apache/james/mime4j/field/UnstructuredField.java#1 $
 */
public class UnstructuredField extends Field {
    private String value;
    
    protected UnstructuredField(String name, String body, String raw, String value) {
        super(name, body, raw);
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    public static class Parser implements FieldParser {
        public Field parse(final String name, final String body, final String raw) {
            final String value = DecoderUtil.decodeEncodedWords(body);
            return new UnstructuredField(name, body, raw, value);
        }
    }
}
