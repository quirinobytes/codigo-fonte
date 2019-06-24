#!/usr/bin/env python

import boto3
ddb = boto3.client('dynamodb')
ddb.describe_limits()

